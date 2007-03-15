#ifndef _COMMON_H_
#define _COMMON_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "util/list.h" // modified linked-list from linux
#include "key.h" // SSH key data-structure

#define MAX_PACKET_LEN 1400

#define TYPE_FETCH_REQ 0x01
#define TYPE_FETCH_REPLY_PARTIAL 0x02
#define TYPE_FETCH_REPLY_FINAL 0x03
#define TYPE_PROBE_REQ 0x04
#define TYPE_PROBE_REPLY 0x05

// all fields should be in network byte order 

typedef struct {
	uint8_t version;
	uint8_t msg_type;
	uint16_t service_type;
	uint16_t service_port;
	uint16_t name_len;
	uint16_t total_len;
} __attribute__ ((packed)) notary_header;


#define SSH_KEYTYPE_DSA 0x1
#define SSH_KEYTYPE_RSA 0x2
#define SSH_KEYTYPE_RSA1 0x3


// ssh-key data structure used in packet replies
typedef struct {
	uint16_t key_len_bytes;
	uint16_t num_probes;
	uint32_t ip_addr;
} __attribute__ ((packed)) ssh_key_info;

#define KEY_INFO_SIZE(info)  \
	sizeof(ssh_key_info) + info->key_len_bytes \
	+ (sizeof(int) * info->num_probes)

typedef struct {
	struct list_head list;
	ssh_key_info *info;	
} ssh_key_info_list;


#define min(X, Y)  ((X) < (Y) ? (X) : (Y))


#endif
