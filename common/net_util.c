
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/wait.h>
#include "common.h"

// see if  client entered an RFC 1918 address at the command
// line.  If so, probing is useless so just print a warning
// and continue.
int is_rfc1918(char *hostname) {


	struct in_addr test_net, net1, net2,net3;

	// if hostname is DNS name, return false
	if(! inet_aton(hostname, &test_net) )
		return 0;

	uint32_t test_ip = ntohl(test_net.s_addr);

	int ret = inet_aton("10.0.0.0", &net1);
	assert(ret);
	uint32_t mask = 0xff000000; // slash 8
	if( (test_ip & mask) == (ntohl(net1.s_addr)))
		return 1;

        ret = inet_aton("192.168.0.0", &net2);
	assert(ret);
	mask = 0xffff0000; // slash 16
	if( (test_ip & mask) == (ntohl(net2.s_addr)))
		return 1;

        ret = inet_aton("172.16.0.0", &net3);
	assert(ret);
	mask = 0xfff00000; // slash 12
	if( (test_ip & mask) == (ntohl(net3.s_addr)))
		return 1;

	return 0;
}


// send data to a local unix socket, identified by 'name'
int sendToUnixSock(char *name, char *buf, int buf_len){
    
    int s, len;
    struct sockaddr_un remote;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "ERROR: socket: %s\n", strerror(errno));
        return -1;
    }
    
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, name);
    //len = SUN_LEN((&remote));
    len = strlen(remote.sun_path) + sizeof(remote.sun_family) + 1;
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        fprintf(stderr, "ERROR: connect: %s\n", strerror(errno));
        return -1;
    }
    
    int n = send(s, buf, buf_len , 0);
    if(n == -1) {
       fprintf(stderr, "ERROR: send: %s\n", strerror(errno));
       return -1;
    }
    close(s);
    return n;
}

int openUnixServerSock(char *name, int max_queue) {
    int s, len;
    struct sockaddr_un local;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "ERROR: socket: %s\n", strerror(errno));
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, name);
    unlink(local.sun_path);

    //len = SUN_LEN((&local));
    len = strlen(local.sun_path) + sizeof(local.sun_family) + 1;
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        fprintf(stderr, "ERROR: bind: %s\n", strerror(errno));
        exit(1);
    }

    if (listen(s,max_queue) == -1) {
        fprintf(stderr, "ERROR: listen: %s\n", strerror(errno));
        exit(1);
    }
    DPRINTF(DEBUG_INFO, "Opened unix sock '%s', sock = %d \n", name, s);
    return s;
}

// given a client server socket, accept a single client
// connection and return all data from that connection
// (up to buf_len bytes) in the caller-allocated 'buf'
int readUnixClientData(int s, char *buf, int buf_len) {
        int n = -1, s2;
        socklen_t t;
        struct sockaddr_un remote;

        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote,
                (socklen_t *)&t)) == -1) {
            fprintf(stderr, "ERROR: accept: %s\n", strerror(errno));
            return -1;
        }

        int so_far = 0;
        while(n != 0 && (so_far < buf_len)) {
          n = recv(s2, buf + so_far, buf_len - so_far, 0);
          if (n < 0){
            fprintf(stderr, "ERROR: recv: %s\n", strerror(errno));
            break;
          }
          so_far += n;
        }
      
      close(s2);
      
      return so_far;
}


char *ip_2_str(uint32_t ip) {
  return inet_ntoa(*(struct in_addr*)&ip);
}

uint32_t str_2_ip(char* ip_str) {
  int ip;
  inet_aton(ip_str, (struct in_addr*)&ip);
  return ip;
}

// expects IP to be in network byte order
// note: caller should free memory!
// return 0 on success
int getDNSFromIP(uint32_t ip_addr, char** name) {
  struct hostent *h;

  h = gethostbyaddr((char*)&ip_addr, sizeof(uint32_t),AF_INET);

  if(h == NULL) {
    *name = strdup(ip_2_str(ip_addr));
    return 1;
  } else {
    *name = strdup(h->h_name);
    return 0;
  }
}

int getDNSFromIPstr(char *ip_str, char** name) {
  return getDNSFromIP(str_2_ip(ip_str), name);
}

// return 0 on success
int getIPFromDNS(char *dns_name, uint32_t* addr_out) {
  struct hostent *h;

  if( (h = gethostbyname2(dns_name,AF_INET)) == NULL) {
    fprintf(stderr, "ERROR: gethostbyname error for %s : %s \n",
            dns_name, hstrerror(h_errno));
    return h_errno;
  }
//  fprintf(stderr, "DEBUG: canonical: %s \n", h->h_name);

//  char** pptr;
//  for(pptr = h->h_aliases; *pptr != NULL; pptr++)
//    fprintf(stderr, "DEBUG: \talias: %s \n", *pptr);
  
  *addr_out = *(uint32_t*)*(h->h_addr_list);
//  fprintf(stderr, "DEBUG: IP: %s \n", ip_2_str(*addr_out));
  
  return 0;
}

char *getConfirmedDNSFromIP(uint32_t ip_addr) {
  char *dns_name;
  int error = getDNSFromIP(ip_addr, &dns_name);
  if(error) goto failed;
  
  uint32_t ip_again;
  error = getIPFromDNS(dns_name, &ip_again);
  if(error || ip_addr != ip_again) goto failed;

  return dns_name;
  
  failed:
      free(dns_name);
      return strdup(ip_2_str(ip_addr));
}


/*
int main(int argc, char** argv) {

  if(argc == 2)
    fprintf(stderr, "DEBUG: confirmed: %s \n", getConfirmedDNSFromIP(str_2_ip(argv[1])));
   // fprintf(stderr, "DEBUG: %s \n", getDNSFromIPstr(argv[1]));
  return 0;
}
*/

