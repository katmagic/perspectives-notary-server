

#include "common.h"

char * ssh_fingerprint_hex(u_char *dgst_raw, u_int dgst_raw_len);
void print_key_info_timespans(ssh_key_info* info);
void print_ssh_key(ssh_key_info* info);
void print_key_info_list(ssh_key_info_list* info_list);
ssh_key_info_list *list_from_data(char *buf, int data_len, int sig_len);
void free_key_info_list(ssh_key_info_list* info_list);
void initialize_header(notary_header *hdr, uint16_t total_len, 
                        char*hostname, int name_len,
                        uint16_t service_type,
                        uint16_t msg_type);

void add_observation_to_list(ssh_key_info_list *info_list, 
      char *digest, int digest_len, int key_type, int timestamp);
unsigned int data_from_list(ssh_key_info_list *info_list, 
                    char* buf_out, int max_size);
