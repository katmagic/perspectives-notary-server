/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notary_util.h"
#include "common.h"
#include "net_util.h"
#include "notary_crypto.h"
#include "contact_notary.h"

//unsigned int notary_debug = DEBUG_ERROR | DEBUG_SOCKET | DEBUG_INFO | DEBUG_CRYPTO;
unsigned int notary_debug = DEBUG_ERROR;

#define TIMEOUT 8
#define NUM_RETRIES 3
#define SVG_DURATION 200

int main(int argc, char *argv[]){
  if (argc < 3 || argc > 4) { 
    printf("Usage: <notary-file> <service-id> <text|svg|json>\n");
    exit(1);
  }
  SSHNotary *notary = init_ssh_notary();
  load_notary_server_file(notary, argv[1]); 
  fetch_notary_observations(notary, argv[2], 
      TIMEOUT, NUM_RETRIES);

  // NOTE: a really client would likely take the 
  // key received by the application and pass it to a
  // ``policy'' function like check_quorum_duration()
  // in notary-client/client_policy.c to decide whether
  // to accept or reject that key based on the observations
  // This simple client just prints out the results. 

  if (argc == 4){
    if (!strcmp(argv[3],"svg")){
      printf(get_reply_as_svg(argv[2],notary,SVG_DURATION)); 
    }
    else if(!strcmp(argv[3],"json")){
      printf(get_reply_as_json(notary));    
    }
    else if(!strcmp(argv[3],"xml")){
      printf(get_reply_as_xml(notary));    
    }
    else {
      print_notary_reply(stdout, notary);
    }
  }
  else {
    print_notary_reply(stdout, notary);
  }

  free_ssh_notary(notary);
  return 0;
}

