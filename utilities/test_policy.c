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
#include "client_policy.h"

//unsigned int notary_debug = DEBUG_ERROR | DEBUG_SOCKET | DEBUG_INFO | DEBUG_CRYPTO;
unsigned int notary_debug = DEBUG_ERROR;

#define TIMEOUT 1
#define NUM_RETRIES 2

#define QUORUM_SIZE 1
#define QUORUM_DURATION_SEC 1
#define MAX_STALE_SEC INT_MAX
#define KEY_LEN 16

char * keybuf_from_filename(char *fname) {
  FILE *f = fopen(fname, "r");
  char line[128];
  if(!fgets(line, 128, f)) {
    printf("couldn't read: %s \n", fname);
    exit(1);
  }

  char * buf = (char*)malloc(KEY_LEN); 
  int len_out = hexstr_2_buf(line, buf, KEY_LEN); 
  if(len_out != KEY_LEN) {
     printf("error, only read %d key bytes, expected %d \n",
              len_out, KEY_LEN);
      exit(1);
  }
  return buf;
}

int main(int argc, char **argv)
{

   if (argc != 4) { 
      printf("Usage: <notary-file> <service-id>  <key-hash-file> \n");
      exit(1);
   }

   char *key_buf = keybuf_from_filename(argv[3]);

   SSHNotary *notary = init_ssh_notary();
   load_notary_servers(notary, argv[1]); 
   fetch_notary_observations(notary, argv[2], 
            TIMEOUT, NUM_RETRIES);
   print_notary_reply(notary);

   printf("checking quorum \n");
   BOOL result = check_quorum_duration(notary, key_buf, KEY_LEN, SSH_RSA, 
                                          QUORUM_SIZE, 
                                          QUORUM_DURATION_SEC, 
                                          MAX_STALE_SEC);

   printf("quorum-check result = %d \n", result);
   free_ssh_notary(notary);
   return 0;
}

