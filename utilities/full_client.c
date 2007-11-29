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

#define TIMEOUT 1
#define NUM_RETRIES 2

int main(int argc, char *argv[])
{

   if (argc != 3) { 
      printf("Usage: <notary-file> <service-id>  \n");
      exit(1);
   }

   SSHNotary *notary = init_ssh_notary();
   load_notary_server_file(notary, argv[1]); 
   fetch_notary_observations(notary, argv[2], 
            TIMEOUT, NUM_RETRIES);
   print_notary_reply(stdout, notary);

   // NOTE: a really client would likely also take the 
   // key received by the application and pass it to a
   // ``policy'' function like check_quorum_duration()
   // in notary-client/client_policy.c to decide whether
   // to accept or reject that key based on the observations
   
   free_ssh_notary(notary);
   return 0;
}

