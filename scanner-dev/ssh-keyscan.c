/* $OpenBSD: ssh-keyscan.c,v 1.73 2006/08/03 03:34:42 deraadt Exp $ */
/*
 * Copyright 1995, 1996 by David Mazieres <dm@lcs.mit.edu>.
 *
 * Modification and redistribution in source and binary forms is
 * permitted provided that due credit is given to the author and the
 * OpenBSD project by leaving this copyright notice intact.
 */

#include "includes.h"
 
//#include "openbsd-compat/sys-queue.h"
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

#include "../common.h"
#include "mysql_storage.h" // for NO_KEY
#include "../debug.h"
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

#include "patricia.h"    
#include "mysql.h"
#include <stdio.h>


/* Flag indicating whether IPv4 or IPv6.  This can be set on the command line.
   Default value is AF_UNSPEC means both IPv4 and IPv6. */
int IPv4or6 = AF_UNSPEC;

int ssh_port = SSH_DEFAULT_PORT;

int hash_hosts = 0;		/* Hash hostname on output */

#define MAXMAXFD 256

/* The number of seconds after which to give up on a TCP connection */
int timeout = 5;

#define MAX_TIMEOUTS 1

int maxfd;
#define MAXCON (maxfd - 10)

extern char *__progname;
fd_set *read_wait;
size_t read_wait_nfdset;
int ncon;
int nonfatal_fatal = 0;
jmp_buf kexjmp;
Key *kexjmp_key;

unsigned int notary_debug = (DEBUG_NONE);

static int conrecycle_with_dsa(uint32_t ip, uint16_t port);

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
	char rsa_failed; 
	ssh_key_holder holder;  /* holds info about the requester for a 'on-demand' probe */
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
		error("%s: invalid packet type", c->holder.name);
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

	kexjmp_key = NULL;

	packet_set_connection(c->c_fd, c->c_fd);
	enable_compat20();
	myproposal[PROPOSAL_SERVER_HOST_KEY_ALGS] = 
		c->holder.key_type == KEY_DSA?
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
	if(kexjmp_key == NULL && c->holder.key_type == KEY_RSA){
		c->rsa_failed = 1;
	}
	packet_close();

	return j < 0? NULL : kexjmp_key;
}

static int
tcpconnect(uint32_t ip_addr, uint16_t port)
{
	int s = -1;
	struct sockaddr_in peer;

	peer.sin_family = AF_INET;
	memcpy((char*)&peer.sin_addr.s_addr, (char*)&ip_addr, sizeof(uint32_t));
	peer.sin_port = htons(port);


	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		error("socket: %s", strerror(errno));
		return s;
	}
	if (set_nonblock(s) == -1)
		fatal("%s: set_nonblock(%d)", __func__, s);
	if (connect(s, &peer, sizeof(peer)) < 0 && errno == EINPROGRESS){
		// non-blocking socket should return EINPROGRESS
		return s;
	} else {
		DPRINTF(DEBUG_ERROR, "connect : %s", strerror(errno));
	} 
	close(s);
	s = -1;
	
	return s;
}

int
conalloc(uint32_t ip_addr, uint16_t service_port, uint16_t key_type)
{
	int s;


	s = tcpconnect(ip_addr, service_port);
	
	// connect is non-blocking, so normal failure
	// should not happen here
	if(s == -1) return -1;

	if (s >= maxfd)
		fatal("conalloc: fdno %d too high", s);
	if (fdcon[s].c_status)
		fatal("conalloc: attempt to reuse fdno %d", s);

	char buf[32];
	strcpy(buf, inet_ntoa(*(struct in_addr*)&ip_addr));
	DPRINTF(DEBUG_INFO, "TCP connection started for: %s (s = %d)\n", buf, s);

	fdcon[s].c_fd = s;
	fdcon[s].c_status = CS_CON;
	fdcon[s].c_data = (char *) &fdcon[s].c_plen;
	fdcon[s].c_len = 4;
	fdcon[s].c_off = 0;
	fdcon[s].rsa_failed = 0;
	fdcon[s].holder.port = service_port;
	fdcon[s].holder.key_type = key_type;
	fdcon[s].holder.conn = NULL;
	fdcon[s].holder.key = NULL;
	fdcon[s].holder.ip_addr = ip_addr;
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
	if (s >= maxfd)
		fatal("confree: freeing invalid fdno %d", s);
	
	if(fdcon[s].c_status == CS_UNUSED)
		fatal("confree: free in UNUSED state fdno %d", s);
	close(s);
	if (fdcon[s].c_status == CS_KEYS)
		xfree(fdcon[s].c_data);
	fdcon[s].c_status = CS_UNUSED;
	fdcon[s].holder.key_type = NO_KEY;
	TAILQ_REMOVE(&tq, &fdcon[s], c_link);
	FD_CLR(s, read_wait);
	DPRINTF(DEBUG_INFO, "freeing conn with s = %d \n", s);
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

// after a connection times out, this allocates a new
// connection to try again
static int
conrecycle_with_dsa(uint32_t ip, uint16_t port)
{
	
	DPRINTF(DEBUG_INFO, "recycling with DSA for %s. \n", 
		inet_ntoa(*(struct in_addr*)&ip));
	return conalloc(ip, port, KEY_DSA);
}

void save_key(ssh_key_holder *ssh_keys, int *num_holders_used, con* c){
	memcpy(&ssh_keys[*num_holders_used], &(c->holder), sizeof(ssh_key_holder));
	(*num_holders_used)++;
}

static void
congreet(int s, ssh_key_holder *ssh_keys, int *num_holders_used)
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
		char buf[32];
		strncpy(buf,  inet_ntoa(*(struct in_addr*)&c->holder.ip_addr), 32);
		switch (errno) {
		case EPIPE:
			printf( "%s: Connection closed by remote host\n", buf);
			break;
		case ECONNREFUSED:
			break;
		default:
			DPRINTF(DEBUG_ERROR, "read (%s): %s", buf, strerror(errno));
			break;
		}
		save_key(ssh_keys, num_holders_used,c);
		confree(s);
		return;
	}
	if (*cp != '\n' && *cp != '\r') {
		error("%s: bad greeting", c->holder.name);
		save_key(ssh_keys, num_holders_used,c);
		confree(s);
		return;
	}
	*cp = '\0';
	if (sscanf(buf, "SSH-%d.%d-%[^\n]\n",
	    &remote_major, &remote_minor, remote_version) == 3)
		compat_datafellows(remote_version);
	else
		datafellows = 0;
	if (c->holder.key_type != KEY_RSA1) {
		if (!ssh2_capable(remote_major, remote_minor)) {
			DPRINTF(DEBUG_ERROR, "%s doesn't support ssh2 \n", c->holder.name);
			save_key(ssh_keys, num_holders_used,c);
			confree(s);
			return;
		}
	} else if (remote_major != 1) {
		DPRINTF(DEBUG_ERROR, "%s doesn't support ssh1", c->holder.name);
		save_key(ssh_keys, num_holders_used,c);
		confree(s);
		return;
	}
	n = snprintf(buf, sizeof buf, "SSH-%d.%d-CMU-ResearchScanner\r\n",
	    c->holder.key_type == KEY_RSA1? PROTOCOL_MAJOR_1 : PROTOCOL_MAJOR_2,
	    c->holder.key_type == KEY_RSA1? PROTOCOL_MINOR_1 : PROTOCOL_MINOR_2);
	if (n < 0 || (size_t)n >= sizeof(buf)) {
		error("snprintf: buffer too small");
		save_key(ssh_keys, num_holders_used,c);
		confree(s);
		return;
	}
	if (atomicio(vwrite, s, buf, n) != (size_t)n) {
		error("write (%s): %s", c->holder.name, strerror(errno));
		save_key(ssh_keys, num_holders_used,c);
		confree(s);
		return;
	}

	if (c->holder.key_type != KEY_RSA1) {
		c->holder.key = keygrab_ssh2(c);
		if(c->rsa_failed) {
			uint32_t ip = c->holder.ip_addr;
			uint16_t port = c->holder.port;
			// don't save key...
		   	confree(s);	
			conrecycle_with_dsa(ip, port);
		}else {
			DPRINTF(DEBUG_INFO, "save key2 for s = %d \n", s);
			save_key(ssh_keys, num_holders_used,c);
			confree(s);
		}
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
		congreet(s, ssh_keys, num_holders_used);  // congreet grabs the key for SSH2
		return;
	}
	n = atomicio(read, s, c->c_data + c->c_off, c->c_len - c->c_off);
	if (n == 0) {
		DPRINTF(DEBUG_ERROR, "read (%s): %s", inet_ntoa(*(struct in_addr*)&c->holder.ip_addr), 
			strerror(errno));
		save_key(ssh_keys, num_holders_used,c);
		confree(s);
		return;
	}
	c->c_off += n;

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
			c->holder.key = keygrab_ssh1(c);
			DPRINTF(DEBUG_ERROR, "saving key1 for s = %d \n", s);
			save_key(ssh_keys, num_holders_used,c);
			confree(s);
			return;	
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

	// find the time until the next connection times out
	// and allow select to sleep only until that time
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
		seltime.tv_sec = seltime.tv_usec = 0;  // return immeadiately

	r = xcalloc(read_wait_nfdset, sizeof(fd_mask));
	e = xcalloc(read_wait_nfdset, sizeof(fd_mask));
	memcpy(r, read_wait, read_wait_nfdset * sizeof(fd_mask));
	memcpy(e, read_wait, read_wait_nfdset * sizeof(fd_mask));

	while (select(maxfd, r, NULL, e, &seltime) == -1 &&
	    (errno == EAGAIN || errno == EINTR))
		;

	for (i = 0; i < maxfd; i++) {
		if (FD_ISSET(i, e)) {
			DPRINTF(DEBUG_ERROR, "%s: exception!\n", 
				inet_ntoa(*(struct in_addr*)&fdcon[i].holder.ip_addr));
			save_key(ssh_keys, &num_holders_used,&fdcon[i]);
			confree(i);
		} else if (FD_ISSET(i, r)){
			// we will see if a key is returned here
			DPRINTF(DEBUG_INFO, " reading data from: %s \n", 
				inet_ntoa(*(struct in_addr*)&fdcon[i].holder.ip_addr));
			conread(i, ssh_keys, &num_holders_used);
		}

	}
	xfree(r);
	xfree(e);

	// loop through everything in order of soonest timeout
	c = TAILQ_FIRST(&tq);

	while (c && (c->c_tv.tv_sec < now.tv_sec ||
	    (c->c_tv.tv_sec == now.tv_sec && c->c_tv.tv_usec < now.tv_usec))) {
		//timeout
		int s = c->c_fd;
		// save with a NULL key, and give up
/*		DPRINTF(DEBUG_ERROR, "Failed to get a response from %s : %d "
			" after %d timeouts \n", c->holder.name, 
			c->holder.port, MAX_TIMEOUTS);	
*/
		// just save a null key and free, no timeout
		DPRINTF(DEBUG_INFO, "time is up for: %d \n", s);
		save_key(ssh_keys, &num_holders_used,c);
		confree(s);

		c = TAILQ_NEXT(c, c_link);
	}


	return num_holders_used;
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


MYSQL * init_sql_conn() {

       char *server = "localhost";
       char *user = "root";
       char *password = "moosaysthecow";
       char *database = "ssh";
       
       MYSQL *mysql = mysql_init(NULL);
       
       /* Connect to database */
       if (!mysql_real_connect(mysql, server,
             user, password, database, 0, NULL, 0)) {
          fprintf(stderr, "%s\n", mysql_error(mysql));
          exit(0);
       }
	return mysql;
}

    #define INSERT_SAMPLE "INSERT INTO ssh.probes(ip,hash,type) VALUES(?,?,?)"

void    sql_add_row(MYSQL *mysql, char *ip_str, char* hash_str, char* type) {
     
       MYSQL_STMT *stmt;
	char ip_buf[16];
	char hash_buf[16];
	unsigned long ip_str_len, hash_str_len, type_len = 1;


	/* Prepare an INSERT query with 3 parameters */
	stmt = mysql_stmt_init(mysql);
	if (!stmt){
  		fprintf(stderr, " mysql_stmt_init(), out of memory\n");
  		exit(0);
	}
	if (mysql_stmt_prepare(stmt, INSERT_SAMPLE, strlen(INSERT_SAMPLE)))
	{
  		fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
  		fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  		exit(0);
	}

	/* Get the parameter count from the statement */
	int param_count= mysql_stmt_param_count(stmt);

	if (param_count != 3) /* validate parameter count */
	{
  		fprintf(stderr, " invalid parameter count returned by MySQL\n");
  		exit(0);
	}

	/* Bind the data for first two parameters */
	/* the timestamp will default to the current time */
	MYSQL_BIND    bind[3];
	memset(bind, 0, sizeof(bind));
	
	/* IP address as string */
	bind[0].buffer_type= MYSQL_TYPE_STRING;
	bind[0].buffer= (char *)ip_buf;
	bind[0].buffer_length= 16;
	bind[0].is_null= 0;
	bind[0].length= &ip_str_len;

	/* partial hash as string */
	bind[1].buffer_type= MYSQL_TYPE_STRING;
	bind[1].buffer= (char *)hash_buf;
	bind[1].buffer_length= 16;
	bind[1].is_null= 0;
	bind[1].length= &hash_str_len;

	/* type as string */
	bind[2].buffer_type= MYSQL_TYPE_STRING;
	bind[2].buffer= (char *)type;
	bind[2].buffer_length= 2;
	bind[2].is_null= 0;
	bind[2].length= &type_len;

	/* Bind the buffers */
	if (mysql_stmt_bind_param(stmt, bind))
	{
  		fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  		fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  		exit(0);
	}
	
	// extra careful
	ip_str_len = strlen(ip_str);
	hash_str_len = strlen(hash_str);
	if(ip_str_len > 15 || hash_str_len > 15) {
		DPRINTF(DEBUG_ERROR, "strings are too long: %s or %s \n", 
			ip_str, hash_str);
		exit(0);
	}
	strncpy(ip_buf, ip_str, ip_str_len);
	strncpy(hash_buf, hash_str, hash_str_len);


	/* Execute the INSERT statement - 1*/
	if (mysql_stmt_execute(stmt))
	{
  		fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
  		fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  		exit(0);
	}

	/* Get the total rows affected */
	int affected_rows= mysql_stmt_affected_rows(stmt);

	if (affected_rows != 1) /* validate affected rows */
	{
  		fprintf(stderr, " invalid affected rows by MySQL\n");
  		exit(0);
	}
	DPRINTF(DEBUG_INFO, "Added DB row for %s \n", ip_str);

    }



int probe_list(MYSQL* mysql, uint32_t *ip_addr_list, int num_ips, 
		uint16_t service_port)
{
	ssh_key_holder *ssh_keys;
	ssh_keys = (ssh_key_holder*) malloc(sizeof(ssh_key_holder) * num_ips);

	if(num_ips + 2 >= MAXCON) {
		DPRINTF(DEBUG_ERROR, "Do not have capacity to do %d probes \n", num_ips);
		return -1;
	}

	printf("Beginning Probe Set (%d) \n", num_ips);
	
	int i;
	for(i = 0; i < num_ips; i++) {
		conalloc(ip_addr_list[i], service_port, KEY_RSA);
	}
	
    int total_used = 0;
    int rows_added = 0;	
    while(total_used < num_ips) {
	
	int num_holders_used = conloop(ssh_keys, num_ips);

	if(num_holders_used > 0) {	
		total_used += num_holders_used;
		DPRINTF(DEBUG_INFO, "used %d total holders \n", total_used );	
		for(int i = 0; i < num_holders_used; i++) {
			ssh_key_holder *h = (&ssh_keys[i]);
			char buf[32];
			strcpy(buf, inet_ntoa(*(struct in_addr*)&h->ip_addr));
			if(h->key != NULL) {
				char *p = key_fingerprint(h->key, SSH_FP_MD5, SSH_FP_HEX);
				char short_str[16];
				strncpy(short_str, p, 16);
				short_str[15] = 0;
				char* type = h->key_type == KEY_RSA ? "R" : "D";
				DPRINTF(DEBUG_INFO, "%s has fp %s (%s) \n", buf, short_str, type);	
				sql_add_row(mysql, buf, short_str, type);
				++rows_added;
				xfree(p);
			
			}else {
				DPRINTF(DEBUG_INFO, "key null for %s \n", buf);
			}
		}
	}
   } // end while	

   printf("All %d connections closed.  Found %d keys. \n", total_used, rows_added);

   free(ssh_keys);
   return 1;
}


int load_file(char* fname, uint32_t **ip_list) {
	FILE *fp;
	char line[100];
	char *c;

   	fp = fopen(fname, "r");
   	if (fp == NULL){
      		printf("Failed to open file '%s'\n", fname);
      		exit(1);
   	}
	c = fgets(line, 100, fp); // read in num IP addresses
	if(c == NULL) {
		printf("First line of the file must contain the number of IP addrs \n");
		exit(1);
	}
	int num_ips = atoi(line);
	*ip_list = (uint32_t*) malloc(sizeof(uint32_t) * num_ips);

	int i;
   	for(i = 0; i < num_ips; i++) {
      		c = fgets(line, 100, fp);  /* get one line from the file */
         	DPRINTF(DEBUG_INFO, "line: %s", line);     
		inet_aton(line, (struct in_addr*) &(*ip_list)[i]);
	}

   	fclose(fp);
	return num_ips;
}


#define SCAN_GROUP_SIZE 40

int main(int argc, char** argv) {

	patricia_tree_t *exceptions;
	exceptions = New_Patricia(32);
	load_db_to_trie(exceptions, "exceptions");

	uint32_t *ip_addr_list;
	
	init_scankeys();
	MYSQL *mysql = init_sql_conn();

	if(argv[1][0] == 'f'){	
		// probe all IP's in a file
		if(argc != 3) {
			printf("usage: scanner f <fname>\n");
			exit(1);
		}
		uint32_t size = load_file(argv[2], &ip_addr_list);	
		probe_list(mysql, ip_addr_list, size, 22);
		free(ip_addr_list);
	}else {
		if(argc !=3) {
			printf("usage: scanner <start IP> <num IPs> \n");
			exit(1);
		}
		uint32_t start_addr;
		inet_aton(argv[1], (struct in_addr*)&start_addr);
		start_addr = ntohl(start_addr);
		uint32_t total_ips = atoi(argv[2]);
		ip_addr_list = (uint32_t*)malloc(sizeof(uint32_t) * SCAN_GROUP_SIZE);		
		uint32_t stop_ip = start_addr + total_ips;  
		
		while(stop_ip > start_addr) {
			uint32_t count = 0, ip = 0, i = 0;
			while(1) {
				if(count == SCAN_GROUP_SIZE) break;
				if(start_addr + i == stop_ip) break;

				ip = htonl(start_addr + i);
				if(!ip_in_trie(exceptions, ip)) {
					ip_addr_list[i] = ip;
					count++;
				}else {
					DPRINTF(DEBUG_INFO, "Skipping IP: %s \n",
						inet_ntoa(*(struct in_addr*)&ip));
				}
				i++;
			}
			probe_list(mysql, ip_addr_list, count, 22);
			start_addr += count; 
		}
		free(ip_addr_list);
	}
       
	mysql_close(mysql);
	Destroy_Patricia(exceptions, (void*)0);	

	return 0;
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


