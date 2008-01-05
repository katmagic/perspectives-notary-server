
#include "file_list_convert.h"
#include "notary_util.h"

#define MAX_DATA_SIZE 10000
#define KEY_DATA_SIZE 16

// 'f' must point to a file that contains ssh_key_info_lists 
// objects in text format, e.g.: 
// 
// Start Host: 'finest-hotels.net:22' 
// ssh-rsa key: 35:92:ef:05:4a:64:34:22:01:ad:60:e9:39:b4:8b:4b 
// start:   1189635794 - Wed Sep 12 18:23:14 2007
// end:     1189911308 - Sat Sep 15 22:55:08 2007
//
// End Host
//
// this function will read one of those entries, and return
// it as an ssh key-info object.  
ssh_key_info_list *read_key_info_from_file(FILE *f){
  char data[MAX_DATA_SIZE]; 
  int data_len = MAX_DATA_SIZE;
  read_key_data_from_file(f, data, &data_len); 
    
  if(data_len == 0) return NULL; 

  // there's not signature on this data
  ssh_key_info_list *info_list = list_from_data(data, data_len, 0);
  return info_list; 
}


// when calling, data_len should describe max-size of buf_out
// on return, data_len indicates actual number of useful bytes in buf_out
void read_key_data_from_file(FILE *f, char *buf_out, int *data_len) { 

  char data[MAX_DATA_SIZE]; 
  char buf[1024];
  char hostname[512];
  while(fgets(buf, 1024,f) != NULL) {

    int ret = sscanf(buf, "Start Host: '%s' ", hostname);
    if(ret == EOF) {
      printf("error \n");
      continue;
    }
    if(ret != 1) {
      printf("error, ret = %d \n", ret);
      continue;
    }
    int hostname_len = strlen(hostname);
    hostname[hostname_len - 1] = 0x0; // sscanf misses a single quote
    --hostname_len;
    make_lowercase(hostname, hostname_len); 
    DPRINTF(DEBUG_CONVERT, "host: '%s' \n", hostname);

    memcpy(data, hostname, hostname_len + 1); // copy null terminator
    int offset = hostname_len + 1;

    // read in key-records until we get reach an 'End Host' line
    while(1) {
      char key[64], key_type[32]; 
      fgets(buf, 1024, f);
      if(strcmp(buf,"End Host\n") == 0) break;

      sscanf(buf, "%s key: %s\n", key_type, key); 
      DPRINTF(DEBUG_CONVERT, 
          "key-type = '%s'  key = '%s' \n", key_type, key);
      if(strlen(key) > (3 * KEY_DATA_SIZE)) {
        printf("warning, key data is bigger than expected! \n");
      }

      ssh_key_info *k_info = (ssh_key_info*) (data + offset);
      offset += sizeof(ssh_key_info); 
      k_info->key_len_bytes = htons(KEY_DATA_SIZE);
      k_info->key_type = str_2_keytype(key_type);
      if(k_info->key_type == 255) {
        printf("error, bad key-type (%s) for %s \n", 
            key_type, hostname);
      }
      int num_bytes = hexstr_2_buf(key, data + offset, KEY_DATA_SIZE);
      if(num_bytes != KEY_DATA_SIZE) {
        printf("Error, wrong KEY_DATA_SIZE (expected %d got %d from "
            " key = '%s' \n", KEY_DATA_SIZE, num_bytes, key);
        exit(1); 
      }
      offset += KEY_DATA_SIZE; 


      int timespan_count = 0;
      while(1) {

        int start, end; 
        fgets(buf, 1024, f);
        if(*buf == '\n') {
          DPRINTF(DEBUG_CONVERT, "end of key entry \n");
          break;
        }
        sscanf(buf,"start: %d ", &start);
        fgets(buf, 1024, f);
        sscanf(buf,"end: %d ", &end);
        int net_start = htonl(start);
        memcpy(data + offset, (char*)&net_start, sizeof(int));
        DPRINTF(DEBUG_CONVERT, "start:\t %d \n", start);
        offset += sizeof(int); 
        int net_end = htonl(end); 
        memcpy(data + offset, (char*)&net_end, sizeof(int));
        DPRINTF(DEBUG_CONVERT, "end:\t %d \n", end);
        offset += sizeof(int); 
        ++timespan_count;
      } // done while(1) reading in all timespans

      k_info->num_timespans = htons(timespan_count);
    

    } // done while(1) reading all keys for a single host

    int total_len = offset - (hostname_len + 1);
    if(total_len > *data_len) {
      DPRINTF(DEBUG_ERROR, 
          "buf given to read_key_data_from_file is too small\n"); 
      total_len = *data_len; 
    }
    char *data_start = (data + hostname_len + 1);
    memcpy(buf_out, data_start, total_len);
    *data_len = total_len; 
    return; 

  } 
  *data_len = 0; 
  return; 
}

