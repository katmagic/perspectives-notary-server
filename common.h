#ifndef _COMMON_H_
#define _COMMON_H_

#include "util/list.h"
#include "key.h"
#include <assert.h>

#define MAX_PACKET_LEN 1400
#define NOTARY_SERVER_PORT 2222

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

// ssh-key data struture used in memory
typedef struct {
	struct list_head list;
	Key* key;
	uint32_t ip_addr;
	int32_t time_observed;		
} ssh_key_list;

// ssh-key data structure used in packet replies
typedef struct {
	uint16_t key_type;
	uint16_t key_len_bytes;
	uint32_t ip_addr;
	int32_t time_observed; 
} __attribute__ ((packed)) ssh_key_info;

#endif
