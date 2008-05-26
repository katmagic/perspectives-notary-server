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

unsigned int notary_debug = DEBUG_ERROR | DEBUG_POLICY;
//unsigned int notary_debug = DEBUG_ERROR;

int main(int argc, char **argv){

  if (argc != 6) { 
    printf("Usage: <obs-file> <test-key> <key-type>"
        " <quorum-thresh> <quorum-duration> <max-stale-days>\n");
    exit(1);
  }

  int key_type = str_2_keytype(argv[3]); 
  char * key_buf = (char*)malloc(KEY_LEN); 
  int len_out = hexstr_2_buf(argv[2], key_buf, KEY_LEN); 
  if(len_out != KEY_LEN) {
    printf("error, only read %d key bytes, expected %d \n",
        len_out, KEY_LEN);
    exit(1);
  }

  int quorum_thresh  = atoi(argv[4]); 
  int q_duration     = atoi(argv[5]);
  int max_stale_days = atoi(argv[6]); 
  int max_stale_secs = DAY2SEC(max_stale_days); 

  Notary *notary = load_fake_replies_from_file(argv[1]); 

  BOOL is_cur_consistent; 
  uint32_t duration = get_quorum_duration(notary, key_buf, KEY_LEN, key_type, 
      quorum_thresh, max_stale_secs, &is_cur_consistent);

  print_policy_results(notary, key_buf, KEY_LEN, key_type, quorum_thresh, 
      q_duration, max_stale_secs, is_cur_consistent, duration);
  print_notary_reply(stdout, notary); 
  printf("\n"); 

  return 0;
}

