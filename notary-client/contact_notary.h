#ifndef CONTACT_NOTARY_H_
#define CONTACT_NOTARY_H_

#include "common.h"
#include "net_util.h"
#include "notary_local.h"


void send_single_query(server_list *server, int sock,  
                           notary_header *hdr);
int recv_single_reply(int sock, char *buf, int buf_len, struct sockaddr_in *addr) ;
void fetch_notary_observations(SSHNotary *notary, 
		char* service_id, int timeout_secs, int num_retries);
#endif
