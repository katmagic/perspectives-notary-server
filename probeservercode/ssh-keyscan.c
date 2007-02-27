/* $OpenBSD: ssh-keyscan.c,v 1.73 2006/08/03 03:34:42 deraadt Exp $ */
/*
 * Copyright 1995, 1996 by David Mazieres <dm@lcs.mit.edu>.
 *
 * Modification and redistribution in source and binary forms is
 * permitted provided that due credit is given to the author and the
 * OpenBSD project by leaving this copyright notice intact.
 */

#include "includes.h"
 
#include "openbsd-compat/sys-queue.h"
#include <sys/resource.h>
#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif

#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/bn.h>

#include <netdb.h>
#include <errno.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "xmalloc.h"
#include "ssh.h"
#include "ssh1.h"
#include "buffer.h"
#include "key.h"
#include "cipher.h"
#include "kex.h"
#include "openbsd-compat/sys-queue.h"

#include "compat.h"
#include "myproposal.h"
#include "packet.h"
#include "dispatch.h"
#include "log.h"
#include "atomicio.h"
#include "misc.h"
#include "hostfile.h"

#include "probe_server.h"

/* Flag indicating whether IPv4 or IPv6.  This can be set on the command line.
   Default value is AF_UNSPEC means both IPv4 and IPv6. */
int IPv4or6 = AF_UNSPEC;

int ssh_port = SSH_DEFAULT_PORT;

#define KT_RSA1	1
#define KT_DSA	2
#define KT_RSA	4

// default to all key types
int get_keytypes = KT_RSA1 | KT_RSA | KT_DSA;

int hash_hosts = 0;		/* Hash hostname on output */

#define MAXMAXFD 256

/* The number of seconds after which to give up on a TCP connection */
int timeout = 5;

int maxfd;
#define MAXCON (maxfd - 10)

extern char *__progname;
fd_set *read_wait;
size_t read_wait_nfdset;
int ncon;
int nonfatal_fatal = 0;
jmp_buf kexjmp;
Key *kexjmp_key;




/*
 * Keep a connection structure for each file descriptor.  The state
 * associated with file descriptor n is held in fdcon[n].
 */
typedef struct Connection {
	u_char c_status;	/* State of connection on this file desc. */
#define CS_UNUSED 0		/* File descriptor unused */
#define CS_CON 1		/* Waiting to connect/read greeting */
#define CS_SIZE 2		/* Waiting to read initial packet size */
#define CS_KEYS 3		/* Waiting to read public key packet */
	int c_fd;		/* Quick lookup: c->c_fd == c - fdcon */
	int c_plen;		/* Packet length field for ssh packet */
	int c_len;		/* Total bytes which must be read. */
	int c_off;		/* Length of data read so far. */
	int c_keytype;		/* Only one of KT_RSA1, KT_DSA, or KT_RSA */
	char *c_namebase;	/* Address to free for c_name and c_namelist */
	char *c_name;		/* Hostname of connection for errors */
	char *c_namelist;	/* Pointer to other possible addresses */
	char *c_output_name;	/* Hostname of connection for output */
	char *c_data;		/* Data read from this fd */
	Kex *c_kex;		/* The key-exchange struct for ssh2 */
	struct timeval c_tv;	/* Time at which connection gets aborted */
	TAILQ_ENTRY(Connection) c_link;	/* List of connections in timeout order. */
} con;









TAILQ_HEAD(conlist, Connection) tq;	/* Timeout Queue */
con *fdcon;

/*
 *  This is just a wrapper around fgets() to make it usable.
 */

static int
fdlim_get(int hard)
{
#if defined(HAVE_GETRLIMIT) && defined(RLIMIT_NOFILE)
	struct rlimit rlfd;

	if (getrlimit(RLIMIT_NOFILE, &rlfd) < 0)
		return (-1);
	if ((hard ? rlfd.rlim_max : rlfd.rlim_cur) == RLIM_INFINITY)
		return SSH_SYSFDMAX;
	else
		return hard ? rlfd.rlim_max : rlfd.rlim_cur;
#else
	return SSH_SYSFDMAX;
#endif
}

static int
fdlim_set(int lim)
{
#if defined(HAVE_SETRLIMIT) && defined(RLIMIT_NOFILE)
	struct rlimit rlfd;
#endif

	if (lim <= 0)
		return (-1);
#if defined(HAVE_SETRLIMIT) && defined(RLIMIT_NOFILE)
	if (getrlimit(RLIMIT_NOFILE, &rlfd) < 0)
		return (-1);
	rlfd.rlim_cur = lim;
	if (setrlimit(RLIMIT_NOFILE, &rlfd) < 0)
		return (-1);
#elif defined (HAVE_SETDTABLESIZE)
	setdtablesize(lim);
#endif
	return (0);
}

/*
 * This is an strsep function that returns a null field for adjacent
 * separators.  This is the same as the 4.4BSD strsep, but different from the
 * one in the GNU libc.
 */
static char *
xstrsep(char **str, const char *delim)
{
	char *s, *e;

	if (!**str)
		return (NULL);

	s = *str;
	e = s + strcspn(s, delim);

	if (*e != '\0')
		*e++ = '\0';
	*str = e;

	return (s);
}


static Key *
keygrab_ssh1(con *c)
{
	static Key *rsa;
	static Buffer msg;

	if (rsa == NULL) {
		buffer_init(&msg);
		rsa = key_new(KEY_RSA1);
	}
	buffer_append(&msg, c->c_data, c->c_plen);
	buffer_consume(&msg, 8 - (c->c_plen & 7));	/* padding */
	if (buffer_get_char(&msg) != (int) SSH_SMSG_PUBLIC_KEY) {
		error("%s: invalid packet type", c->c_name);
		buffer_clear(&msg);
		return NULL;
	}
	buffer_consume(&msg, 8);		/* cookie */

	/* server key */
	(void) buffer_get_int(&msg);
	buffer_get_bignum(&msg, rsa->rsa->e);
	buffer_get_bignum(&msg, rsa->rsa->n);

	/* host key */
	(void) buffer_get_int(&msg);
	buffer_get_bignum(&msg, rsa->rsa->e);
	buffer_get_bignum(&msg, rsa->rsa->n);

	buffer_clear(&msg);

	return (rsa);
}

static int
hostjump(Key *hostkey)
{
	kexjmp_key = hostkey;
	longjmp(kexjmp, 1);
}

static int
ssh2_capable(int remote_major, int remote_minor)
{
	switch (remote_major) {
	case 1:
		if (remote_minor == 99)
			return 1;
		break;
	case 2:
		return 1;
	default:
		break;
	}
	return 0;
}

static Key *
keygrab_ssh2(con *c)
{
	int j;

	packet_set_connection(c->c_fd, c->c_fd);
	enable_compat20();
	myproposal[PROPOSAL_SERVER_HOST_KEY_ALGS] = c->c_keytype == KT_DSA?
	    "ssh-dss": "ssh-rsa";
	c->c_kex = kex_setup(myproposal);
	c->c_kex->kex[KEX_DH_GRP1_SHA1] = kexdh_client;
	c->c_kex->kex[KEX_DH_GRP14_SHA1] = kexdh_client;
	c->c_kex->kex[KEX_DH_GEX_SHA1] = kexgex_client;
	c->c_kex->kex[KEX_DH_GEX_SHA256] = kexgex_client;
	c->c_kex->verify_host_key = hostjump;

	if (!(j = setjmp(kexjmp))) {
		nonfatal_fatal = 1;
		dispatch_run(DISPATCH_BLOCK, &c->c_kex->done, c->c_kex);
		fprintf(stderr, "Impossible! dispatch_run() returned!\n");
		exit(1);
	}
	nonfatal_fatal = 0;
	xfree(c->c_kex);
	c->c_kex = NULL;
	packet_close();

	return j < 0? NULL : kexjmp_key;
}

void
keyprint(con *c, Key *key)
{
	char *host = c->c_output_name ? c->c_output_name : c->c_name;

	if (!key)
		return;
	if (hash_hosts && (host = host_hash(host, NULL, 0)) == NULL)
		fatal("host_hash failed");

	fprintf(stdout, "%s ", host);
	key_write(key, stdout);
	fputs("\n", stdout);
}

static int
tcpconnect(char *host)
{
	struct addrinfo hints, *ai, *aitop;
	char strport[NI_MAXSERV];
	int gaierr, s = -1;

	snprintf(strport, sizeof strport, "%d", ssh_port);
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = IPv4or6;
	hints.ai_socktype = SOCK_STREAM;
	if ((gaierr = getaddrinfo(host, strport, &hints, &aitop)) != 0)
		fatal("getaddrinfo %s: %s", host, gai_strerror(gaierr));
	for (ai = aitop; ai; ai = ai->ai_next) {
		s = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		if (s < 0) {
			error("socket: %s", strerror(errno));
			continue;
		}
		if (set_nonblock(s) == -1)
			fatal("%s: set_nonblock(%d)", __func__, s);
		if (connect(s, ai->ai_addr, ai->ai_addrlen) < 0 &&
		    errno != EINPROGRESS)
			error("connect (`%s'): %s", host, strerror(errno));
		else
			break;
		close(s);
		s = -1;
	}
	freeaddrinfo(aitop);
	return s;
}

int
conalloc(char *iname, char *oname, int keytype)
{
	char *namebase, *name, *namelist;
	int s;

	namebase = namelist = xstrdup(iname);

	do {
		name = xstrsep(&namelist, ",");
		if (!name) {
			xfree(namebase);
			return (-1);
		}
	} while ((s = tcpconnect(name)) < 0);

	if (s >= maxfd)
		fatal("conalloc: fdno %d too high", s);
	if (fdcon[s].c_status)
		fatal("conalloc: attempt to reuse fdno %d", s);

	fdcon[s].c_fd = s;
	fdcon[s].c_status = CS_CON;
	fdcon[s].c_namebase = namebase;
	fdcon[s].c_name = name;
	fdcon[s].c_namelist = namelist;
	fdcon[s].c_output_name = xstrdup(oname);
	fdcon[s].c_data = (char *) &fdcon[s].c_plen;
	fdcon[s].c_len = 4;
	fdcon[s].c_off = 0;
	fdcon[s].c_keytype = keytype;
	gettimeofday(&fdcon[s].c_tv, NULL);
	fdcon[s].c_tv.tv_sec += timeout;
	TAILQ_INSERT_TAIL(&tq, &fdcon[s], c_link);
	FD_SET(s, read_wait);
	ncon++;
	return (s);
}

static void
confree(int s)
{
	if (s >= maxfd || fdcon[s].c_status == CS_UNUSED)
		fatal("confree: attempt to free bad fdno %d", s);
	close(s);
	xfree(fdcon[s].c_namebase);
	xfree(fdcon[s].c_output_name);
	if (fdcon[s].c_status == CS_KEYS)
		xfree(fdcon[s].c_data);
	fdcon[s].c_status = CS_UNUSED;
	fdcon[s].c_keytype = 0;
	TAILQ_REMOVE(&tq, &fdcon[s], c_link);
	FD_CLR(s, read_wait);
	ncon--;
}

static void
contouch(int s)
{
	TAILQ_REMOVE(&tq, &fdcon[s], c_link);
	gettimeofday(&fdcon[s].c_tv, NULL);
	fdcon[s].c_tv.tv_sec += timeout;
	TAILQ_INSERT_TAIL(&tq, &fdcon[s], c_link);
}

static int
conrecycle(int s)
{
	con *c = &fdcon[s];
	int ret;

	ret = conalloc(c->c_namelist, c->c_output_name, c->c_keytype);
	confree(s);
	return (ret);
}

static void
congreet(int s)
{
	int n = 0, remote_major = 0, remote_minor = 0;
	char buf[256], *cp;
	char remote_version[sizeof buf];
	size_t bufsiz;
	con *c = &fdcon[s];

	for (;;) {
		memset(buf, '\0', sizeof(buf));
		bufsiz = sizeof(buf);
		cp = buf;
		while (bufsiz-- &&
		    (n = atomicio(read, s, cp, 1)) == 1 && *cp != '\n') {
			if (*cp == '\r')
				*cp = '\n';
			cp++;
		}
		if (n != 1 || strncmp(buf, "SSH-", 4) == 0)
			break;
	}
	if (n == 0) {
		switch (errno) {
		case EPIPE:
			error("%s: Connection closed by remote host", c->c_name);
			break;
		case ECONNREFUSED:
			break;
		default:
			error("read (%s): %s", c->c_name, strerror(errno));
			break;
		}
		conrecycle(s);
		return;
	}
	if (*cp != '\n' && *cp != '\r') {
		error("%s: bad greeting", c->c_name);
		confree(s);
		return;
	}
	*cp = '\0';
	if (sscanf(buf, "SSH-%d.%d-%[^\n]\n",
	    &remote_major, &remote_minor, remote_version) == 3)
		compat_datafellows(remote_version);
	else
		datafellows = 0;
	if (c->c_keytype != KT_RSA1) {
		if (!ssh2_capable(remote_major, remote_minor)) {
			debug("%s doesn't support ssh2", c->c_name);
			confree(s);
			return;
		}
	} else if (remote_major != 1) {
		debug("%s doesn't support ssh1", c->c_name);
		confree(s);
		return;
	}
	// prints the version too, which we don't care about
	fprintf(stderr, "# %s %s\n", c->c_name, chop(buf));
	n = snprintf(buf, sizeof buf, "SSH-%d.%d-OpenSSH-keyscan\r\n",
	    c->c_keytype == KT_RSA1? PROTOCOL_MAJOR_1 : PROTOCOL_MAJOR_2,
	    c->c_keytype == KT_RSA1? PROTOCOL_MINOR_1 : PROTOCOL_MINOR_2);
	if (n < 0 || (size_t)n >= sizeof(buf)) {
		error("snprintf: buffer too small");
		confree(s);
		return;
	}
	if (atomicio(vwrite, s, buf, n) != (size_t)n) {
		error("write (%s): %s", c->c_name, strerror(errno));
		confree(s);
		return;
	}
	if (c->c_keytype != KT_RSA1) {
		printf("Whoops, switching to SSH2 !!!\n");
		keyprint(c, keygrab_ssh2(c));
		confree(s);
		return;
	}
	c->c_status = CS_SIZE;
	contouch(s);
}

static void
conread(int s, ssh_key_holder *ssh_keys, int *num_holders_used)
{
	con *c = &fdcon[s];
	size_t n;

	if (c->c_status == CS_CON) {
		congreet(s);
		return;
	}
	n = atomicio(read, s, c->c_data + c->c_off, c->c_len - c->c_off);
	if (n == 0) {
		error("read (%s): %s", c->c_name, strerror(errno));
		confree(s);
		return;
	}
	c->c_off += n;

	Key *key;
	if (c->c_off == c->c_len)
		switch (c->c_status) {
		case CS_SIZE:
			c->c_plen = htonl(c->c_plen);
			c->c_len = c->c_plen + 8 - (c->c_plen & 7);
			c->c_off = 0;
			c->c_data = xmalloc(c->c_len);
			c->c_status = CS_KEYS;
			break;
		case CS_KEYS:
			// everything supports SSH1?
			key = keygrab_ssh1(c);
			keyprint(c, key);
			printf("got key on %d, calling confree \n",s);
			confree(s);
			ssh_keys[*num_holders_used].name = 
				xmalloc(strlen(c->c_output_name));
			strcpy(ssh_keys[*num_holders_used].name, 
					c->c_output_name);
			ssh_keys[*num_holders_used].key = key;
			(*num_holders_used)++;
			
		default:
			fatal("conread: invalid status %d for con = %d", 
				c->c_status, s);
			break;
		}

	contouch(s);
}

int conloop(ssh_key_holder *ssh_keys, int num_holders) {

	struct timeval seltime, now;
	fd_set *r, *e;
	con *c;
	int i;

	bzero(ssh_keys, sizeof(ssh_key_holder) * num_holders);
	int num_holders_used = 0;

	gettimeofday(&now, NULL);
	c = TAILQ_FIRST(&tq);

	if (c && (c->c_tv.tv_sec > now.tv_sec ||
	    (c->c_tv.tv_sec == now.tv_sec && c->c_tv.tv_usec > now.tv_usec))) {
		seltime = c->c_tv;
		seltime.tv_sec -= now.tv_sec;
		seltime.tv_usec -= now.tv_usec;
		if (seltime.tv_usec < 0) {
			seltime.tv_usec += 1000000;
			seltime.tv_sec--;
		}
	} else
		seltime.tv_sec = seltime.tv_usec = 0;

	r = xcalloc(read_wait_nfdset, sizeof(fd_mask));
	e = xcalloc(read_wait_nfdset, sizeof(fd_mask));
	memcpy(r, read_wait, read_wait_nfdset * sizeof(fd_mask));
	memcpy(e, read_wait, read_wait_nfdset * sizeof(fd_mask));

	while (select(maxfd, r, NULL, e, &seltime) == -1 &&
	    (errno == EAGAIN || errno == EINTR))
		;

	for (i = 0; i < maxfd; i++) {
		if (FD_ISSET(i, e)) {
			error("%s: exception!", fdcon[i].c_name);
			confree(i);
		} else if (FD_ISSET(i, r)){
			// we will see if a key is returned here
			conread(i, ssh_keys, &num_holders_used);
		}

		if(num_holders_used > num_holders) 
			break; // save the rest for later
	}
	xfree(r);
	xfree(e);

	c = TAILQ_FIRST(&tq);
	while (c && (c->c_tv.tv_sec < now.tv_sec ||
	    (c->c_tv.tv_sec == now.tv_sec && c->c_tv.tv_usec < now.tv_usec))) {
		int s = c->c_fd;

		c = TAILQ_NEXT(c, c_link);
		conrecycle(s);
	}

	return num_holders_used;
}

// returns 1 if we have space to probe this host, else 0
int do_host(char *host)
{
	if(ncon + KT_RSA >= MAXCON) return 0;

	for (int j = KT_RSA1; j <= KT_RSA; j *= 2) {
		if (get_keytypes & j) {
			conalloc(host, host, j);
		}
	}
	return 1;
}

void
fatal(const char *fmt,...)
{
	va_list args;

	va_start(args, fmt);
	do_log(SYSLOG_LEVEL_FATAL, fmt, args);
	va_end(args);
	if (nonfatal_fatal)
		longjmp(kexjmp, -1);
	else
		exit(255);
}


void init_scankeys() {


	init_rng();
	seed_rng();
	TAILQ_INIT(&tq);

	/* Ensure that fds 0, 1 and 2 are open or directed to /dev/null */
	sanitise_stdfd();

	maxfd = fdlim_get(1);
	if (maxfd < 0)
		fatal("%s: fdlim_get: bad value", __progname);
	if (maxfd > MAXMAXFD)
		maxfd = MAXMAXFD;
	if (MAXCON <= 0)
		fatal("%s: not enough file descriptors", __progname);
	if (maxfd > fdlim_get(0))
		fdlim_set(maxfd);
	fdcon = xcalloc(maxfd, sizeof(con));

	read_wait_nfdset = howmany(maxfd, NFDBITS);
	read_wait = xcalloc(read_wait_nfdset, sizeof(fd_mask));

}
