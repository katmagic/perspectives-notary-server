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

#include "list.h" // modified linked-list from linux
//#include "key.h" // SSH key data-structure
#include "debug.h"

#ifndef TRUE 
 #define TRUE 1
 #define FALSE 0
#endif

#define SERVICE_TYPE_SSH 1
#define SERVICE_TYPE_SSL 2

#define BOOL uint8_t

#define MAX_NAME_LEN 128
#define SIGNATURE_LEN 172
#define MAX_PACKET_LEN 4000
#define KEY_LEN 16

#define TYPE_FETCH_REQ 0x01
#define TYPE_FETCH_REPLY_PARTIAL 0x02
#define TYPE_FETCH_REPLY_FINAL 0x03
#define TYPE_PROBE_REQ 0x04
#define TYPE_PROBE_REPLY 0x05

// all fields should be in network byte order 

typedef struct {
	uint8_t version;
	uint8_t msg_type;
	uint16_t total_len;
	uint16_t service_type;
	uint16_t name_len;
        uint16_t sig_len;
} __attribute__ ((packed)) notary_header;



// data structure used in packet replies
// all fields should be in network byte order 
// NOTE: this is used for all types of keys, 
// not just SSH keys
typedef struct {
        uint16_t num_timespans;
	uint16_t key_len_bytes;
        uint8_t key_type;
} __attribute__ ((packed)) ssh_key_info;


#define SSH_RSA1 0
#define SSH_RSA 1
#define SSH_DSA 2
#define SSL_ANY 3

#define KEY_INFO_SIZE(info)  \
	sizeof(ssh_key_info) + ntohs(info->key_len_bytes) \
	+ (2 * sizeof(int) * ntohs(info->num_timespans))

#define HEADER_SIZE(hdr)  \
	(sizeof(notary_header) + \
              ntohs(hdr->name_len)) 

#define FIND_TIMESPANS(info) \
      ((int*)(((char*)(info + 1)) + ntohs(info->key_len_bytes)))

// TODO: this struct is useless, as there should simply be a 
// list_head elem in the ssh_key_info struct.  However, i currently
// don't feel like changing all the code that uses this struct, so it
// stays for now.  
typedef struct {
	struct list_head list;
	ssh_key_info* info;	
} ssh_key_info_list;

#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))

#define SEC2MIN(x) ((float)x/60.0)
#define SEC2HOUR(x) ((float)x/3600.0)
#define SEC2DAY(x) ((float)x/86400.0)

#define DAY2SEC(x) ((int) (x * 86400.0))


#endif
