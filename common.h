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
#include "debug.h"

#define TRUE 1
#define FALSE 0
#define BOOL uint8_t

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


//#define SSH_KEYTYPE_DSA 0x1
//#define SSH_KEYTYPE_RSA 0x2
//#define SSH_KEYTYPE_RSA1 0x3


// ssh-key data structure used in packet replies
typedef struct {
	uint16_t key_len_bytes;
	uint16_t num_probes;
	uint32_t ip_addr;
} __attribute__ ((packed)) ssh_key_info;


#define KEY_INFO_SIZE(info)  \
	sizeof(ssh_key_info) + ntohs(info->key_len_bytes) \
	+ (sizeof(int) * ntohs(info->num_probes))

typedef struct {
	struct list_head list;
	notary_header* hdr;	
} ssh_msg_list;

typedef struct {
	struct list_head list;
	Key* key;
	int num_probes;
	int *timestamps; // sorted list of the probe times, oldest to newest
	int *addresses;
} ssh_result_list;

#define HDR2DATA(hdr) \
	(((char*)hdr) + sizeof(notary_header) \
	+ ntohs(hdr->name_len)) 

#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))

#define SEC2MIN(x) ((float)x/60.0)
#define SEC2HOUR(x) ((float)x/3600.0)
#define SEC2DAY(x) ((float)x/86400.0)


#endif
