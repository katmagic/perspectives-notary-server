#ifndef _COMMON_H_
#define _COMMON_H_


#define MAX_PACKET_LEN 1400
#define NOTARY_SERVER_PORT 2222

#define TYPE_FETCH_REQ 0x01
#define TYPE_FETCH_REPLY_PARTIAL 0x02
#define TYPE_FETCH_REPLY_FINAL 0x03
#define TYPE_PROBE_REQ 0x04
#define TYPE_PROBE_REPLY 0x05

#define SERVICE_SSH 0x01

// all fields should be in network byte order 

typedef struct {
	uint8_t version;
	uint8_t msg_type;
	uint16_t service_type;
	uint16_t service_port;
	uint16_t name_len;
} __attribute__ ((packed)) notary_header;


#define SSH_KEYTYPE_DSA 0x1
#define SSH_KEYTYPE_RSA 0x2

typedef struct {
	uint8_t key_type;
	uint16_t key_len_bytes;
} __attribute__ ((packed)) ssh_key_info;

#endif
