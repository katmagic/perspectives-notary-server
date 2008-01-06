
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


// send data to a local unix socket, identified by 'name'
int sendToUnixSock(char *name, char *buf, int buf_len){ 
    
    int s, len;
    struct sockaddr_un remote;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }
    
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, name);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        return -1;
    }
    
    int n = send(s, buf, buf_len , 0);
    if(n == -1) {
       perror("send");
       return -1;
    }
    close(s);
    return n; 
}

int openUnixServerSock(char *name) {
    int s, len;
    struct sockaddr_un local;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("unix socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, name);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("unix bind");
        exit(1);
    }

    if (listen(s, 5) == -1) {
        perror("unix listen");
        exit(1);
    }
    DPRINTF(DEBUG_INFO, "Opened unix sock '%s', sock = %d \n",
		name, s);
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
            perror("accept");
            return -1;
        }

        int so_far = 0;
        while(n != 0 && (so_far < buf_len)) { 
          n = recv(s2, buf + so_far, buf_len - so_far, 0);
          if (n < 0){ 
            perror("recv");
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
    printf("gethostbyname error for %s : %s \n",
            dns_name, hstrerror(h_errno));
    return h_errno;
  }
//  printf("canonical: %s \n", h->h_name);

//  char** pptr;
//  for(pptr = h->h_aliases; *pptr != NULL; pptr++)
//    printf("\talias: %s \n", *pptr);
  
  *addr_out = *(uint32_t*)*(h->h_addr_list);
//  printf("IP: %s \n", ip_2_str(*addr_out));
 
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
    printf("confirmed: %s \n", getConfirmedDNSFromIP(str_2_ip(argv[1])));
   // printf("%s \n", getDNSFromIPstr(argv[1]));
  return 0;
}
*/

