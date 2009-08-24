


#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>

#include "notary_util.h" 
#include "net_util.h"
#include "keyscan_util.h"

// function used by spawned client processes to report resulting key back to
// the main scanner process.  called from sshconnect.c
int record_key(char *dns_name, uint32_t ip_addr, uint16_t port,
                  uint8_t* digest, uint32_t digest_len, uint32_t key_type,  
		  char *server_version_string, uint8_t service_type){

    char full_name[MAX_NAME_LEN];
    snprintf(full_name,MAX_NAME_LEN,"%s:%d,%d",dns_name, port, service_type); 

    int name_len = strlen(full_name);

    int version_len = strlen(server_version_string);

    int total_len = name_len +  digest_len 
          + version_len + 12; // ip-addr, port, key_type, null-byte X 2 = 12
    char * buf = (char*)malloc(total_len);
    char *ptr = buf;
    memcpy(ptr, full_name, name_len + 1);
    ptr += name_len + 1;
    memcpy(ptr, server_version_string, version_len + 1);
    ptr += version_len + 1;
    memcpy(ptr, &ip_addr, 4);
    ptr += 4;
    memcpy(ptr, &port, 2);
    ptr += 2;
    memcpy(ptr, &key_type, 4);
    ptr += 4;
    memcpy(ptr, digest, digest_len);

    int res = sendToUnixSock(FINISHED_CHILD_SOCK_NAME, buf, total_len); 
    free(buf);
  
    if(res < 0) {
        printf("Failed to report probe to recording socket for: \n"); 
        printf("'%s' = '%s' \n", full_name,
            buf_2_hexstr((char*)digest, digest_len));
	return 1;  
    }
    return 0; 
}

