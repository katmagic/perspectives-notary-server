#ifndef CONTACT_NOTARY_H_
#define CONTACT_NOTARY_H_

#include "prio.h" 
#include "prnetdb.h" 

extern "C" { 
#include "net_util.h"
#include "notary_local.h"
} 

void send_single_query(server_list *server, PRFileDesc *fd,  
                           notary_header *hdr);
int recv_single_reply(PRFileDesc *fd, char *buf, int buf_len, PRNetAddr *from) ;
void fetch_notary_observations(SSHNotary *notary, 
		char* service_id, int timeout_secs, int num_retries);
#endif
