/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "client_policy.h"
#include "file_list_convert.h"
#include "notary_util.h"
#include "client_test.h"
#include "contact_notary.h" 

#define TIMEOUT 4
#define NUM_RETRIES 3

unsigned int notary_debug = DEBUG_ERROR | DEBUG_POLICY;
//unsigned int notary_debug = DEBUG_ERROR;

int main(int argc, char **argv) {
   
  if (argc != 7) { 
      printf("Usage: <service> <notary-list>"
          " <test-key> <key-type> <quorum-thresh> <max-stale-days>\n");
      exit(1);
   }

  int key_type = str_2_keytype(argv[4]); 
  char * key_buf = (char*)malloc(KEY_LEN); 
  int len_out = hexstr_2_buf(argv[3], key_buf, KEY_LEN); 
  if(len_out != KEY_LEN) {
     printf("error, only read %d key bytes, expected %d \n",
              len_out, KEY_LEN);
      exit(1);
  }
  
  int quorum_thresh = atoi(argv[5]); 
  int max_stale_days = atoi(argv[6]); 
  int max_stale_secs = DAY2SEC(max_stale_days); 

  printf("service: %s\n"
      "notary list: %s\n"
      "test key: %s\n"
      "key type: %s\n"
      "Q: %d\n" 
      "max stale days %d\n", 
      argv[1], argv[2], argv[3], keytype_2_str(key_type), 
      quorum_thresh, max_stale_days);

   SSHNotary *notary = init_ssh_notary();
   load_notary_server_file(notary, argv[2]); 
   fetch_notary_observations(notary, argv[1], 
            TIMEOUT, NUM_RETRIES);
  
  print_notary_reply(stdout, notary); 
  printf("\n"); 

   printf("checking quorum \n");
   BOOL is_cur_consistent; 
   uint32_t duration = get_quorum_duration(notary, key_buf, KEY_LEN, key_type, 
                                   quorum_thresh, max_stale_secs, &is_cur_consistent);

   printf("quorum-duration = %f  days (is_cur_consistent = %d) \n", 
       SEC2DAY(duration), is_cur_consistent);

   return 0;
}

