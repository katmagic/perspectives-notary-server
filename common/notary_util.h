#ifndef _NOTARY_UTIL_H_
#define _NOTARY_UTIL_H_

#include "common.h"

void make_lowercase(char *str, int len);
const char *keytype_2_str(uint8_t type);
uint8_t str_2_keytype(char *str);
char *buf_2_hexstr(char *buf, int buf_len);
int hexstr_2_buf(char * str, char *buf_out, int buf_len); 
void print_key_info_timespans(FILE *f, ssh_key_info* info);
void print_key_info_list(FILE *f, ssh_key_info_list* info_list);
ssh_key_info_list *list_from_data(char *buf, int data_len, int sig_len);
void free_key_info_list(ssh_key_info_list* info_list);
void initialize_header(notary_header *hdr, uint16_t total_len, 
                        char*hostname, int name_len,
                        uint16_t service_type,
                        uint16_t msg_type);

void prune_oldest_timestamp(ssh_key_info_list *info_list, uint32_t cur_time); 

void add_observation_to_list(ssh_key_info_list *info_list, 
      char *digest, int digest_len, int key_type, int timestamp);
unsigned int data_from_list(ssh_key_info_list *info_list, 
                    char* buf_out, int max_size);
int get_key_info_list(char *response, int *response_len, int max_len, ssh_key_info_list *info_list);

#endif
