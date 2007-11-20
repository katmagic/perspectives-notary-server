

#include "common.h"
#include "key.h"  // for SSH keys (TODO: extract to another file)
#include "buffer.h"
#include "mysql.h"

char * ssh_fingerprint_hex(u_char *dgst_raw, u_int dgst_raw_len);
void print_key_info_timespans(ssh_key_info* info);
void print_ssh_key(ssh_key_info* info);
void print_key_info_list(ssh_key_info_list* info_list);
void key_to_buf(Key *key, char** buf, int* buf_len);
Key *buf_to_key(char* buf, int buf_len, int key_type);
Key *info_to_ssh_key(ssh_key_info* info);
ssh_key_info_list *list_from_data(char *buf, int data_len, int sig_len);
void free_key_info_list(ssh_key_info_list* info_list);
void initialize_header(notary_header *hdr, uint16_t total_len, 
                        char*hostname, int name_len,
                        uint16_t service_type,
                        uint16_t msg_type);

unsigned int 
get_reply_data(MYSQL *mysql, int sid, char* buf, int max_size);
char *
key_fingerprint_hex(u_char *dgst_raw, u_int dgst_raw_len);
void add_observation_to_list(ssh_key_info_list *info_list, 
      char *digest, int digest_len, int key_type, int timestamp);
unsigned int data_from_list(ssh_key_info_list *info_list, 
                    char* buf_out, int max_size);
