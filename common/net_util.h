#ifndef _NET_UTIL_H_
#define _NET_UTIL_H_

#include <netdb.h>
#include <stdio.h>
#include <string.h>


#define TIMEVAL_TO_MILLIS(t) \
  ((((float)t->tv_sec) * 1000) + (((float)t->tv_usec) / 1000))   

#define MILLIS_TO_TIMEVAL_SEC(m) (m / 1000)
#define MILLIS_TO_TIMEVAL_USEC(m) (1000 * (((int)m) % 1000))  

#define TIMEVAL_DIFF_MILLIS(t1,t2) \
  ((((float)t1.tv_sec - t2.tv_sec) * 1000) \
   + (((float)t1.tv_usec - t2.tv_usec) / 1000))   

char *ip_2_str(uint32_t ip);

int sendToUnixSock(char *name, char *buf, int buf_len); 

int openUnixServerSock(char *name); 

uint32_t str_2_ip(char* ip_str);

int getDNSFromIP(uint32_t ip_addr, char** name);

int getDNSFromIPStr(char * ip_str, char** name);

int getIPFromDNS(char *dns_name, uint32_t* addr_out);

char *getConfirmedDNSFromIP(uint32_t ip_addr);

#endif

