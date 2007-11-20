#ifndef NOTARY_CLIENT_H_
#define NOTARY_CLIENT_H_

#include "common.h"
#include "net_util.h"
#include "notary_crypto.h"
#include <openssl/rsa.h>


notary_header* create_request(char*hostname, uint16_t service_type);

void send_single_query(struct sockaddr_in *server, int sock,  
                           notary_header *hdr);
int recv_single_reply( int sock, char *buf, int buf_len) ;
ssh_key_info_list* parse_message(char *buf, int msg_len, RSA* pub_key);
#endif
