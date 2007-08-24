#ifndef _NET_UTIL_H_
#define _NET_UTIL_H_

#include <netdb.h>
#include <stdio.h>
#include <string.h>

char *ip_2_str(uint32_t ip);

uint32_t str_2_ip(char* ip_str);

int getDNSFromIP(uint32_t ip_addr, char** name);

int getDNSFromIPStr(char * ip_str, char** name);

int getIPFromDNS(char *dns_name, uint32_t* addr_out);

char *getConfirmedDNSFromIP(uint32_t ip_addr);

#endif

