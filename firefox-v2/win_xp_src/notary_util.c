#include "list.h"
#include "notary_util.h"
#include "common.h"
#include <time.h>

void xfree(void*);



void initialize_header(notary_header *hdr, uint16_t total_len, 
                        char*hostname, int name_len,
                        uint16_t service_type,
                        uint16_t msg_type) {
		char *name_start;
        hdr->version = 1;
        hdr->msg_type = (uint8_t)msg_type; // TODO: fix signature to pass msg_type as uint8_t
        hdr->total_len = htons(total_len);
        hdr->name_len = htons(name_len);
        hdr->service_type = htons(service_type);
        hdr->sig_len = 0;
        name_start = (char*)(hdr+1);
		memcpy(name_start, hostname, name_len);
}

unsigned int 
data_from_list(ssh_key_info_list *info_list, 
                    char* buf_out, int max_size) {
    
        struct list_head *pos,*tmp;
        ssh_key_info_list* cur;

        int offset = 0;
        list_for_each_safe(pos, tmp, &info_list->list) {
			int size;
            cur = list_entry(pos, ssh_key_info_list, list);  
            size = KEY_INFO_SIZE(cur->info);


            if(offset + size <= max_size)
                memcpy(buf_out + offset, cur->info, size);
            else {
                DPRINTF(DEBUG_ERROR, 
                    "insufficient space to convert list to data\n");
                return 0;
            }
                
            offset += size;
            
       }
        
       return offset;
}





// dw: that may be slow.. rethink?
// note: all memory in the list is newly allocated.
// nothing from the packet buffer is used
ssh_key_info_list *list_from_data(char *data_ptr, int data_len,
                                            int sig_len) {
        int total_len = data_len - sig_len;
        int so_far = 0;
		ssh_key_info* ptr = (ssh_key_info*) data_ptr;
        ssh_key_info_list *head = 
          (ssh_key_info_list*)malloc(sizeof(ssh_key_info_list));
        INIT_LIST_HEAD(&(head->list));
        

        while(so_far < total_len) {
              int key_info_size = KEY_INFO_SIZE(ptr);
			  ssh_key_info *info; 
			  ssh_key_info_list *tmp;
              if(key_info_size <= 0) {
                  DPRINTF(DEBUG_ERROR, "invalid key_info size = %d\n",
                      key_info_size);
                  return NULL;
              }
              info = (ssh_key_info*) malloc(key_info_size);
              memcpy(info, ptr, key_info_size);
              tmp = (ssh_key_info_list*) malloc(sizeof(ssh_key_info_list));
              DPRINTF(DEBUG_INFO, "Adding key_info of size = %d bytes to list\n", key_info_size);
              tmp->info = info;
              __list_add(&(tmp->list),&(head->list), head->list.next);
              
              ptr = (ssh_key_info*)(((char*)ptr) + key_info_size);
              so_far += key_info_size;
        }
        return head;
}

// assumes info_list is NOT NULL
// 1-4-2008:  modified this to save and use pointers directly instead 
// of indices into the list and to change how timestamps are updated.  
// revert to SVN copy if things go bad :P 
void add_observation_to_list(ssh_key_info_list *info_list, 
      char *digest, int digest_len, int key_type, int timestamp) {

        // loop through once to find 
        // 1) if there's an entry with this key already
        // 2) which entry is the newest
        struct list_head *pos,*tmp;
        ssh_key_info_list *cur, *most_recent = NULL, *key_match = NULL;

       
        int most_recent_time = 0;
        list_for_each_safe(pos, tmp, &info_list->list) {
		  char *key_buf;
		  int len, num_spans, i; 
		  int *timespans; 

          cur = list_entry(pos, ssh_key_info_list, list);
          key_buf = (char*)(cur->info + 1);
          len = ntohs(cur->info->key_len_bytes);
          if(len == digest_len &&
              cur->info->key_type == key_type && 
              (memcmp(digest, key_buf, len) == 0)) {
              key_match = cur;
          }
          timespans = (int*)(key_buf + len);
          num_spans = ntohs(cur->info->num_timespans);
          for(i = 0; i < num_spans; i++){
              int t_end = ntohl(timespans[1]);
              if(t_end > most_recent_time) {
                  most_recent_time = t_end;
                  most_recent = cur;
              }
              timespans += 2;
          }
          
        } 

        // we always must update the t-end value of the
        // most recent timespan if it exists.  
        // if we observed the same key as last time that is, if:
        // ((most_recent = key_match) && (key_match != NULL))
        // update we update the t-end value to the current time and we're done.
        // otherwise, we need to update the t-end value to be
        // now - 1 seconds and continue
            
        if(most_recent != NULL) { 
          char *mr_key_buf = (char*)(most_recent->info + 1);
          int mr_len = ntohs(most_recent->info->key_len_bytes);
          int *timespans = (int*)(mr_key_buf + mr_len);
          int mr_num_spans = ntohs(most_recent->info->num_timespans);
          int i;
          for(i = 0; i < mr_num_spans; i++){
            int t_end = ntohl(timespans[1]);
            if(t_end == most_recent_time) {
              // this is timespan to update
              
              if(most_recent == key_match) {
                // easy case, we're all done! 
                timespans[1] = htonl(timestamp);
                return;
              } 
              // change t-end value for the old most recent key
              timespans[1] = htonl(timestamp - 1); 
              break;
            }
            timespans += 2;
          }
        }

        // since the key from this probe did not match the most
        // recent key we had seen, there are two options left

        if (key_match != NULL) {
              // we've seen this key before, but it wasn't most recent
              // so we need to add another timespan to an 
              // existing ssh_key_info object 
              // (requires reallocation of memory)
				int *timespans;
                int old_size = KEY_INFO_SIZE(key_match->info);
                int new_size = old_size + (2 * sizeof(int));
                ssh_key_info *new_info = (ssh_key_info*)
                                          malloc(new_size);
                memcpy(new_info, key_match->info, old_size);
                new_info->num_timespans = htons(1 + 
                                    ntohs(key_match->info->num_timespans));
                // add the timespans as the last 8 bytes
                timespans = (int*)(((char*)new_info) + old_size);
                timespans[0] = timespans[1] = htonl(timestamp);
              
                free(key_match->info);
                key_match->info = new_info;
            
        }else {
            // we've never seen this key before  we need to add a 
            // new ssh_key_info entry with 1 timespan to the list.
			char *key_buf;
			int *timespans;
			ssh_key_info_list *tmp;
            ssh_key_info *new_info = (ssh_key_info*) malloc(
                sizeof(ssh_key_info) + digest_len + (2 * sizeof(int)));
            new_info->num_timespans = htons(1);
            new_info->key_type = (uint8_t) key_type;
            new_info->key_len_bytes = htons(digest_len);
            key_buf = (char*)(new_info + 1);
            memcpy(key_buf, digest, digest_len);
            timespans = (int*)(key_buf + digest_len);
            timespans[0] = timespans[1] = htonl(timestamp);

            // add it to the list
            tmp = (ssh_key_info_list*)malloc(sizeof(ssh_key_info_list));
            tmp->info = new_info;
            __list_add(&(tmp->list),&(info_list->list), 
                            info_list->list.next);
        }

}


void print_key_info_timespans(FILE *f, ssh_key_info* info) {
  char *key_buf;
  int len, num_spans, i;
  int *timespans; 

  if(info == NULL) 
    return;

  key_buf = (char*)(info + 1);
  len = ntohs(info->key_len_bytes);
  timespans = (int*)(key_buf + len);
  num_spans = ntohs(info->num_timespans);

  for(i = 0; i < num_spans; i++){
    uint32_t t_start = ntohl(timespans[0]);
    uint32_t t_end = ntohl(timespans[1]);
    //bug fix:  ctime requires time_t, which may be 64-bit
    time_t start_time = (time_t) t_start;
    time_t end_time = (time_t) t_end; 
    fprintf(f, "start:\t %d - %s", t_start, ctime((const time_t*)&start_time));
    fprintf(f, "end:\t %d - %s", t_end, ctime((const time_t*)&end_time));
    timespans += 2;
  }

}

int get_key_info_timespans(char *response, int *response_len, int max_len, ssh_key_info *info)
{
  char *key_buf;
  int n = 0, len, num_spans, i, *timespans;
  if(info == NULL) 
    return -1;

  key_buf = (char*)(info + 1);
  len = ntohs(info->key_len_bytes);
  timespans = (int*)(key_buf + len);
  num_spans = ntohs(info->num_timespans);
  for(i = 0; i < num_spans; i++){
    int t_start = ntohl(timespans[0]);
    int t_end = ntohl(timespans[1]);
    time_t start_time = (time_t) t_start;
    time_t end_time = (time_t) t_end; 
    if(*response_len >= max_len) {
	printf("bailing from get_key_info_timespans 1\n"); 
    	printf("response_len = %d  max_len = %d \n", *response_len, max_len); 
	return 0; 
    }
    //printf("ts1:  response_len = %d  max_len = %d \n", *response_len, max_len); 
    n = snprintf(response + *response_len, max_len - *response_len, "start:\t %d - %s", t_start, ctime((const time_t*)&start_time));
    *response_len += n;
    if(*response_len >= max_len) {
	printf("bailing from get_key_info_timespans 2\n"); 
    	printf("response_len = %d  max_len = %d \n", *response_len, max_len); 
	return 0; 
    } 
    //printf("ts2:  response_len = %d  max_len = %d \n", *response_len, max_len); 
    n = snprintf(response + *response_len, max_len - *response_len, "end:\t %d - %s", t_end, ctime((const time_t*)&end_time));
    *response_len += n;
    timespans += 2;
  }
  return 0;
}



void print_key_info_list(FILE *f, ssh_key_info_list* info_list) {
        struct list_head *pos,*tmp;
        ssh_key_info_list* cur;
		char *key_buf, *str;
		int len; 

        if(info_list == NULL) { 
          fprintf(f, "[NULL LIST]  \n"); 
          return;
        }

		  list_for_each_safe(pos, tmp, &info_list->list) {
          cur = list_entry(pos, ssh_key_info_list, list);

          if(cur->info == NULL) {
              DPRINTF(DEBUG_ERROR, "cur->info should never be null \n");
              exit(1);
          }
          key_buf = (char*)(cur->info + 1);
          len = ntohs(cur->info->key_len_bytes);
          str = buf_2_hexstr(key_buf,len);
          fprintf(f, "%s key: %s \n", keytype_2_str(cur->info->key_type),str);
          free(str);
          print_key_info_timespans(f, cur->info);
          fprintf(f, "\n");
        } 
}


int get_key_info_list(char *response, int *response_len, int max_len, ssh_key_info_list *info_list)
{
		char *key_buf,*str;
		int len;

	    struct list_head *pos,*tmp;
        ssh_key_info_list* cur;
        int n = 0;
        if(info_list == NULL) 
            return -1;


        list_for_each_safe(pos, tmp, &info_list->list) {
          cur = list_entry(pos, ssh_key_info_list, list);

          if(cur->info == NULL) {
              DPRINTF(DEBUG_ERROR, "cur->info should never be null \n");
              return -1;
          }
	  if(*response_len >= max_len) {
		printf("bailing from get_key_info_list1 \n"); 
		return 0; 
 	  } 
          key_buf = (char*)(cur->info + 1);
          len = ntohs(cur->info->key_len_bytes);
          str = buf_2_hexstr(key_buf,len);


          n = snprintf(response + *response_len, max_len - *response_len, "%s key: %s \n", keytype_2_str(cur->info->key_type),
                                  str);
          *response_len += n;                        
	  printf("after key: n = %d response_len = %d \n", n, *response_len); 
          free(str);
          get_key_info_timespans(response, response_len, max_len, cur->info);
	  if(*response_len >= max_len) {
		printf("bailing from get_key_info_list 2 \n"); 
		return 0; 
 	  } 
          n = snprintf(response + *response_len, max_len - *response_len, "\n");
          *response_len += n;
	  printf("after timespans: n = %d response_len = %d \n", n, *response_len); 
        } 
        return 0;
}








void free_key_info_list(ssh_key_info_list* info_list) {

        ssh_key_info_list *l = info_list;
        struct list_head *pos,*tmp;
        ssh_key_info_list* cur;

        if(info_list == NULL) return;


        list_for_each_safe(pos, tmp, &info_list->list) {
          cur = list_entry(pos, ssh_key_info_list, list);

          list_del(pos);
          free(cur->info);
          free(cur);
        }
        free(l);
}



char * buf_2_hexstr(char *dgst_raw, int dgst_raw_len){

	char *retval;
	int i;

    int str_len = dgst_raw_len * 3 + 1;
	retval = (char *)malloc(str_len);
    memset(retval, 0x0, str_len);
	for (i = 0; i < dgst_raw_len; i++) {
		char hex[4];
		snprintf(hex, sizeof(hex), "%02x:", (u_char)dgst_raw[i]);
		strncat(retval, hex, dgst_raw_len * 3 + 1);
	}

	/* Remove the trailing ':' character */
	retval[(dgst_raw_len * 3) - 1] = '\0';
	return retval;
}

int hexstr_2_buf(char * str, char *buf_out, int buf_len) {  
    char *ptr = str;
    int i = 0;
    while(i < buf_len) {
      char *before = ptr; 
      long int v = strtol(ptr, &ptr, 16);
      if(ptr == before) {
         break;
      }

      ++ptr;
      buf_out[i] = (char) v;
      ++i;
    }
    return i;
}

const char *keytype_2_str(uint8_t type) {
  if(type == SSH_RSA1) return "ssh-rsa1";
  if(type == SSH_RSA) return "ssh-rsa";
  if(type == SSH_DSA) return "ssh-dsa";
  if(type == SSL_ANY) return "ssl";
  return "unknown key-type";
}

uint8_t str_2_keytype(char *str) {
  if(strcmp(str,"ssh-rsa1") == 0) return SSH_RSA1;
  if(strcmp(str,"ssh-rsa") == 0) return SSH_RSA;
  if(strcmp(str,"ssh-dsa") == 0) return SSH_DSA;
  if(strcmp(str,"ssl") == 0) return SSL_ANY;
  return 255;
}

void make_lowercase(char *str, int len) {
  int i;
  for(i = 0; i < len; i++) {
      if ((str[i] >= 0x41) && (str[i] <= 0x5a))
        str[i] = (char)(str[i] | 0x20);
  }
}
