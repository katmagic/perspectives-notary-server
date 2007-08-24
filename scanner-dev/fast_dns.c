/* Copyright 1998 by the Massachusetts Institute of Technology.
 *
 * $Id: ahost.c,v 1.19 2007-04-16 15:35:34 yangtse Exp $
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 * M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 */

#include "setup.h"

#if !defined(WIN32) || defined(WATT32)
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ares.h"
#include "ares_dns.h"
#include "inet_ntop.h"
#include "inet_net_pton.h"

#include "../common.h"
#include "net_util.h"
#include "../debug.h"

#ifndef HAVE_STRUCT_IN6_ADDR
struct in6_addr
{
  unsigned char s6_addr[16];
};
#endif

static void ip_2_name_callback(void *arg, int status, struct hostent *host);
static void name_2_ip_callback(void *arg, int status, struct hostent *host);

void do_parallel_dns(ssh_key_holder *ssh_keys, int num_ips)  {
  ares_channel channel;
  int status, nfds;
  fd_set read_fds, write_fds;
  struct timeval *tvp, tv;

  struct ares_options opts;
  opts.timeout = 3;
  opts.tries = 1;
  int opt_mask = (ARES_OPT_TIMEOUT | ARES_OPT_TRIES);
  status = ares_init_options(&channel, &opts, opt_mask);

  if (status != ARES_SUCCESS)
    {
      DPRINTF(DEBUG_ERROR, "ares_init_opt: %s\n", ares_strerror(status));
      return;
    }
  
    for(int i = 0; i < num_ips; i++) {
	ssh_key_holder *h = (&ssh_keys[i]);
        if(h->key != NULL) {
            DPRINTF(DEBUG_INFO, "looking up IP: %s \n", ip_2_str(h->ip_addr));
            ares_gethostbyaddr(channel, &h->ip_addr, sizeof(uint32_t), 
                  AF_INET, ip_2_name_callback, h);
        }
    }


  /* Wait for all queries to complete. */
  while (1)
    {
      FD_ZERO(&read_fds);
      FD_ZERO(&write_fds);
      nfds = ares_fds(channel, &read_fds, &write_fds);
      if (nfds == 0)
        break;
      tvp = ares_timeout(channel, NULL, &tv);
      select(nfds, &read_fds, &write_fds, NULL, tvp);
      ares_process(channel, &read_fds, &write_fds);
    }
    
    for(int i = 0; i < num_ips; i++) {
	ssh_key_holder *h = (&ssh_keys[i]);
        if(h->key != NULL && h->name != NULL) {
            DPRINTF(DEBUG_INFO, "looking up name: %s \n", h->name);
            ares_gethostbyname(channel, h->name, 
                  AF_INET, name_2_ip_callback, h);
        }
    }
  
    /* Wait for all queries to complete. */
  while (1)
    {
      FD_ZERO(&read_fds);
      FD_ZERO(&write_fds);
      nfds = ares_fds(channel, &read_fds, &write_fds);
      if (nfds == 0)
        break;
      tvp = ares_timeout(channel, NULL, &tv);
      select(nfds, &read_fds, &write_fds, NULL, tvp);
      ares_process(channel, &read_fds, &write_fds);
    }
  
    
    for(int i = 0; i < num_ips; i++) {
	ssh_key_holder *h = (&ssh_keys[i]);
        if(h->key != NULL && h->name == NULL) {
            h->name = strdup(ip_2_str(h->ip_addr));
        }
    }
    
  ares_destroy(channel);

}

static void ip_2_name_callback(void *arg, int status, struct hostent *host){

  ssh_key_holder *holder = (ssh_key_holder*)arg;
  if (status != ARES_SUCCESS || host == NULL)
      holder->name = NULL;  
  else    
      holder->name = strdup(host->h_name);
}

static void name_2_ip_callback(void *arg, int status, struct hostent *host){

  ssh_key_holder *holder = (ssh_key_holder*)arg;
  if (status != ARES_SUCCESS || host == NULL) {
      goto invalidate;
  }

  char** p;
  char found = 0;
  for(p = host->h_addr_list; *p; p++) {
    uint32_t answer = *(uint32_t*)*p;
    if(answer == holder->ip_addr){ 
      found = 1;
      break;
    }
  }
  if(!found)
      goto invalidate; 

  return;

  invalidate:
    free(holder->name);
    holder->name = NULL;
}

/*
 *
unsigned int notary_debug = DEBUG_ALL;

int main(int argc, char** argv) {

  int num_ips = 10;
  ssh_key_holder ssh_keys[10];
  bzero(ssh_keys, sizeof(ssh_keys));
  ssh_keys[0].ip_addr = str_2_ip("128.2.222.96");
  ssh_keys[0].key = (Key*)1;
  ssh_keys[1].ip_addr = str_2_ip("128.2.213.64");
  ssh_keys[1].key = (Key*)1;
  ssh_keys[2].ip_addr = str_2_ip("206.197.119.139");
  ssh_keys[2].key = (Key*)1;
  ssh_keys[3].ip_addr = str_2_ip("206.197.119.145");
  ssh_keys[3].key = (Key*)1;
  do_parallel_dns(ssh_keys, num_ips);

}

*/

