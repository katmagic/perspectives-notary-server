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

//unsigned int notary_debug = DEBUG_ERROR | DEBUG_POLICY;
unsigned int notary_debug = DEBUG_ERROR;


// demonstrates & tests the generate of SVG images from 
// notary results. 
int main(int argc, char **argv) {
 
  if (argc != 4) { 
    printf("Usage: <service> <notary-list> <graph duration>\n");
    exit(1);
  }

  SSHNotary *notary   = init_ssh_notary();
  load_notary_server_file(notary, argv[2]); 
  fetch_notary_observations(notary, argv[1], 
      TIMEOUT, NUM_RETRIES);

 
  char *str = get_reply_as_svg(argv[1],notary,atoi(argv[3])); 
  printf(str); 
  free(str); 
  return 0;
}

