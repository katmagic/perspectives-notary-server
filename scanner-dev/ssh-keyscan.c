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

#include "net_util.h"
#include "patricia.h"    
#include "mysql.h"
#include <stdio.h>
#include "fast_dns.h"

// holy hack

unsigned int kill_connection;

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


int long_jump_result;
#define LJ_RESULT_BAD_KEYTYPE 2
#define LJ_RESULT_UNKNOWN_ERROR 4

// used in congreet
#define ERROR_NO_SSH1 -1
#define ERROR_NO_SSH2 -2


unsigned int notary_debug = (DEBUG_ERROR);

static int conrecycle_with_keytype(uint32_t ip, uint16_t port, 
    short key_type);


// defines the number of probes (and DNS lookups) we will 
// do in parallel.  Must be less than the max number of sockets
// supported by the system.
#define SCAN_GROUP_SIZE 128

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

        long_jump_result = 0; // clear it
	if (!(j = setjmp(kexjmp))) {
                // this code is run right after state was
                // saved by setjmp
		nonfatal_fatal = 1;
		dispatch_run(DISPATCH_BLOCK, &c->c_kex->done, c->c_kex);
		fprintf(stderr, "Impossible! dispatch_run() returned!\n");
		exit(1);
	}
        // this code is run after longjmp is called to
        // restore the state saved by setjmp
	nonfatal_fatal = 0;
	xfree(c->c_kex);
	c->c_kex = NULL;
        if(long_jump_result & LJ_RESULT_BAD_KEYTYPE){
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
		error("socket: %s \n", strerror(errno));
		return s;
	}
	if (set_nonblock(s) == -1)
		fatal("%s: set_nonblock(%d)", __func__, s);
	if (connect(s, &peer, sizeof(peer)) < 0 && errno == EINPROGRESS){
		// non-blocking socket should return EINPROGRESS
		return s;
	} else {
		DPRINTF(DEBUG_ERROR, "connect (%s): %s \n", ip_2_str(ip_addr),
                    strerror(errno));
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
	if(s == -1) {
          return -1;
        }
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
conrecycle_with_keytype(uint32_t ip, uint16_t port, short key_type)
{
	
	DPRINTF(DEBUG_INFO, "recycling with key-type %d for %s. \n", 
		key_type, inet_ntoa(*(struct in_addr*)&ip));
	return conalloc(ip, port, key_type);
}

void save_key(ssh_key_holder *ssh_keys, int *num_holders_used, con* c){
	memcpy(&ssh_keys[*num_holders_used], &(c->holder), sizeof(ssh_key_holder));
	(*num_holders_used)++;
}

// return -1 on error (no action necessary)
// return special error code to indicate protocol version failure
// 0 indicates success
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
		switch (errno) {
		case EPIPE:
			printf( "Connection closed by remote host: %s \n",
                            ip_2_str(c->holder.ip_addr));
			break;
		case ECONNREFUSED:
			break;
		default:
			DPRINTF(DEBUG_ERROR, "read (%s): %s \n", 
                            ip_2_str(c->holder.ip_addr), strerror(errno));
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
        c->holder.version_str = strdup(buf);
	if (sscanf(buf, "SSH-%d.%d-%[^\n]\n",
	    &remote_major, &remote_minor, remote_version) == 3)
		compat_datafellows(remote_version);
	else
		datafellows = 0;
	if (c->holder.key_type != KEY_RSA1) {
		if (!ssh2_capable(remote_major, remote_minor)) {
			DPRINTF(DEBUG_INFO, "%s doesn't support ssh2 \n", ip_2_str(c->holder.ip_addr));
			uint32_t ip = c->holder.ip_addr;
			uint16_t port = c->holder.port;
			// don't save key...
		   	confree(s);	
			conrecycle_with_keytype(ip, port, KEY_RSA1);
                        return;
		}
	} else if (remote_major != 1) {
		DPRINTF(DEBUG_ERROR, "%s doesn't support ssh1", ip_2_str(c->holder.ip_addr));
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
		error("write (%s): %s", ip_2_str(c->holder.ip_addr), strerror(errno));
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
			conrecycle_with_keytype(ip, port, KEY_DSA);
		}else {
                        char * valid = (c->holder.key) ? "Found" : "NULL";
			DPRINTF(DEBUG_INFO, "save key2 for s = %d (%s) \n", s, valid);
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
		DPRINTF(DEBUG_ERROR, "read (%s): %s \n", ip_2_str(c->holder.ip_addr), 
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
			DPRINTF(DEBUG_INFO, "saving key1 for s = %d \n", s);
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

void conloop(ssh_key_holder *ssh_keys, int num_holders, int *holder_index) {

	struct timeval seltime, now;
	fd_set *r, *e;
	con *c;
	int i;


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
			save_key(ssh_keys, holder_index,&fdcon[i]);
			confree(i);
		} else if (FD_ISSET(i, r)){
			// we will see if a key is returned here
			DPRINTF(DEBUG_INFO, " reading data from: %s \n", 
				inet_ntoa(*(struct in_addr*)&fdcon[i].holder.ip_addr));
			conread(i, ssh_keys, holder_index);
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
		save_key(ssh_keys, holder_index,c);
		confree(s);

		c = TAILQ_NEXT(c, c_link);
	}


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



int probe_list(MYSQL* mysql, uint32_t *ip_addr_list, int num_ips, 
		uint16_t service_port)
{
	ssh_key_holder *ssh_keys;
	ssh_keys = (ssh_key_holder*) malloc(sizeof(ssh_key_holder) * num_ips);
	bzero(ssh_keys, sizeof(ssh_key_holder) * num_ips);

	if(num_ips + 2 >= MAXCON) {
		DPRINTF(DEBUG_ERROR, "Do not have capacity to do %d probes \n", num_ips);
		return -1;
	}

	printf("Beginning Probe Set of size %d . \n", num_ips);
	printf("Start = %s ", ip_2_str(ip_addr_list[0]));
        printf(" End =  %s \n", ip_2_str(ip_addr_list[num_ips - 1]));
    
        int cur_holder_index = 0;

	int i;
	for(i = 0; i < num_ips; i++) {
		int ret = conalloc(ip_addr_list[i], service_port, KEY_RSA);
                if(ret < 0) {
                    // allocation fails when there is no route to host
                    // or error is locally detected.  give up on those conns
                    printf("failed conn \n");
                    ++cur_holder_index;
                }
	}
    
    struct timeval t;
    gettimeofday(&t,NULL);
    int pre_probe_time = t.tv_sec;

    while(cur_holder_index < num_ips) {
	conloop(ssh_keys, num_ips, &cur_holder_index);
    } // end while	

    gettimeofday(&t,NULL);
    int pre_dns_time = t.tv_sec;

    /*
    // slow serial DNS lookups for now
    printf("Beginning DNS Lookups \n");
    for(int i = 0; i < num_ips; i++) {
	ssh_key_holder *h = (&ssh_keys[i]);
        if(h->key != NULL) {
            printf("looking up: %s \n", ip_2_str(h->ip_addr));
            ssh_keys[i].name = getConfirmedDNSFromIP(h->ip_addr); // need to free this str later
        }
    }*/

    do_parallel_dns(ssh_keys, num_ips);
    
    gettimeofday(&t,NULL);
    int pre_store_time = t.tv_sec;

    printf("Beginning MYSQL inserts \n");

    int keys_found = 0;
    for(int i = 0; i < num_ips; i++) {
	ssh_key_holder *h = (&ssh_keys[i]);
	if(h->key != NULL) {
                ++keys_found;
                store_ssh_probe_result(mysql, h->name, h->port,
                  h->ip_addr, h->key, pre_probe_time, h->version_str) ;
                free(h->name);
                free(h->version_str);
	}
   }

    gettimeofday(&t,NULL);
    int done_time = t.tv_sec;

   int probe_time = pre_dns_time - pre_probe_time;
   int dns_time = pre_store_time - pre_dns_time;
   int store_time = done_time - pre_store_time;

   printf("Found %d keys. Probe Time: %d DNS Time: %d Store Time: %d \n", 
        keys_found,probe_time, dns_time, store_time);

   free(ssh_keys);
   return keys_found;
}



void scan_range(MYSQL *mysql, patricia_tree_t* valid_ips, 
                patricia_tree_t* not_valid_ips, 
                uint32_t start_addr, uint32_t total_ips){

  uint32_t* ip_addr_list = (uint32_t*)
      malloc(sizeof(uint32_t) * SCAN_GROUP_SIZE);
		 
  int total_keys = 0;
  uint32_t ip = 0, total = 0, total_probes = 0;
  while(total != total_ips) {

      int count = 0;
      while(1) {
	 if(count == SCAN_GROUP_SIZE) break;
	 if(total == total_ips) break;

	 ip = htonl(start_addr + total);
         my_bool valid = ip_in_trie(valid_ips, ip);
         my_bool invalid = ip_in_trie(not_valid_ips, ip);

         if(valid && !invalid) {
            ip_addr_list[count] = ip;
            ++count;
         }else {
            DPRINTF(DEBUG_INFO, "Skipping IP: %s \n",
		inet_ntoa(*(struct in_addr*)&ip));
	 }
	 ++total;
      }
      total_probes += count;
      total_keys += probe_list(mysql, ip_addr_list, count, 22); 
 }
 printf("Finished range scan.  Probed %d of %d total addresses."
     " Found %d keys. \n",total_probes, total_ips, total_keys);

 free(ip_addr_list);

}


void scan_table(MYSQL *mysql, patricia_tree_t* valid_ips, 
                patricia_tree_t* not_valid_ips, 
                char *table_name){

		  
  char query_buf[128];
  snprintf(query_buf, 128, "SELECT distinct(ip_addr) from %s", 
        table_name);

  if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0) {
      fprintf(stderr, "Error querying %s for addresses to probe: %s \n",
            table_name, mysql_error(mysql));
            return;
  }
  
  uint32_t* ip_addr_list = (uint32_t*)
      malloc(sizeof(uint32_t) * SCAN_GROUP_SIZE);
  
  int count = 0, total_keys = 0;
  uint32_t total_probes = 0;

  MYSQL_RES *result = mysql_use_result(mysql);
  if(!result) goto end;


  MYSQL_ROW row;
  my_bool done = 0;
  while(!done) {
   
      while(1) {
	 if(count == SCAN_GROUP_SIZE) 
           break; // run this set
         
         if((row = mysql_fetch_row(result)) == NULL) {
              done = 1;
              break; // run final set
         }

	 uint32_t ip = atoi(row[0]);
         my_bool valid = ip_in_trie(valid_ips, ip);
         my_bool invalid = ip_in_trie(not_valid_ips, ip);

         if(valid && !invalid) {
            ip_addr_list[count] = ip;
            ++count;
         }
      } // end while(1)
      total_probes += count;
      total_keys += probe_list(mysql, ip_addr_list, count, 22); 
    
  } // end while(!done)

  end: 

  mysql_free_result(result);
  printf("Finished table scan.  Probed %d of total addresses. "
      " Found %d keys. \n",total_probes, total_keys);

  free(ip_addr_list);

}


void usage() {

  printf("usage: scanner t <valid-table> <exception-table> "
             " <ip-table> \n");
  printf("usage: scanner r <valid-table> <exception-table> "
             " prefix \n");

}

int main(int argc, char** argv) {


        if(argc < 4) {
          usage();
          exit(1);
        }

	patricia_tree_t *not_valid, *valid;
	not_valid = New_Patricia(32);
        valid = New_Patricia(32);
        load_db_to_trie(valid, argv[2]);
        load_db_to_trie(not_valid, argv[3]);
      
	init_scankeys();
	MYSQL *mysql = open_mysql_conn("localhost", "root", "moosaysthecow",
		"ssh");

	if(argc == 5 && argv[1][0] == 't'){	
            scan_table(mysql, valid, not_valid, argv[4]);
	}else if(argc == 5 && argv[1][0] == 'p'){
                prefix_t *prefix;
                prefix = ascii2prefix(AF_INET, argv[4]);
		uint32_t start_addr = *(uint32_t *)&prefix->add.sin;
                int bits = 32 - prefix->bitlen;
                int total_ips = 1 << bits;
                start_addr = ntohl(start_addr);
                Deref_Prefix(prefix);
//		printf("total ips = %d (%d bits). Starts at %s \n", total_ips, bits,
  //                  ip_2_str(htonl(start_addr)));
    //            exit(0);
                scan_range(mysql, valid, not_valid, start_addr, total_ips);
	} else {
            usage();
        }
       
	close_mysql_conn(mysql);
	Destroy_Patricia(not_valid, (void*)0);	
	Destroy_Patricia(valid, (void*)0);	

	return 0;
}

// ah ha!  this is how they "survive"
// fatal errors
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

/*
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
      		c = fgets(line, 100, fp);  // get one line from the file 
         	DPRINTF(DEBUG_INFO, "line: %s", line);     
		inet_aton(line, (struct in_addr*) &(*ip_list)[i]);
	}

   	fclose(fp);
	return num_ips;
}

*/

