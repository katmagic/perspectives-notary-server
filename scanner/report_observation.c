
#include <stdlib.h>
#include "notary_util.h"
#include "keyscan_util.h" 

unsigned int notary_debug = DEBUG_DEFAULT;

int main(int argc, char** argv) {
                 
      if(argc != 7 ) {
        fprintf(stderr, "ERROR: usage: <host> <port> <service-type> "
		"<key-type-str> <md5-fingerprint> <report-sock-name>\n");
        exit(1);
      }
      
      if(strlen(argv[1]) > (MAX_NAME_LEN + 10)) { 
	fprintf(stderr,"ERROR: DNS name / IP '%s' is too long\n", argv[1]); 
	exit(1); 
      }
      char *dns_name = argv[1], key_buf[KEY_LEN];
      uint32_t port = (uint32_t)atoi(argv[2]);
      if(port > 0xffff) { 
	fprintf(stderr, "ERROR: Invalid port number %d \n", port); 
	exit(1); 
      } 
      uint32_t service_type = (uint32_t) atoi(argv[3]);
      if(service_type != SERVICE_TYPE_SSL && 
	 service_type != SERVICE_TYPE_SSH) { 
	fprintf(stderr,"ERROR: Invalid service-type '%d'\n", 
		service_type); 
	exit(1); 
      } 
      int key_str_len = (KEY_LEN * 3) - 1; 
      if(strlen(argv[5]) != key_str_len) { 
	fprintf(stderr, 
	   "ERROR: Need a semi-colon delimited MD5 "
	   "fingerprint of length %d\n", key_str_len);
	exit(1);  
      }
      int len = hexstr_2_buf(argv[5],key_buf,KEY_LEN); 
      if(len != KEY_LEN) { 
	fprintf(stderr, "ERROR: Failed to parse MD5 fingerprint '%s',"
		" len %d != %d \n", argv[5], len, KEY_LEN); 
	exit(1); 
      }
      uint32_t key_type = str_2_keytype(argv[4]); 
      if(key_type == INVALID_KEY_TYPE) { 
	 fprintf(stderr, "ERROR: Invalid key type '%s'\n", argv[4]); 
         exit(1); 
      } 
      return record_key(dns_name, 0 /*no ip address*/, port, key_buf, KEY_LEN, 
			key_type, "", service_type, argv[6]); 
}
