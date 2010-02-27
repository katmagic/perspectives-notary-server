#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#include "db.h"
#include "common.h"
#include "notary_crypto.h"
#include "bdb_storage.h"
#include "notary_util.h"

unsigned int notary_debug = DEBUG_DEFAULT;

DB *db = NULL; 

void close_db(int signal) {
  fprintf(stderr, "WARNING: Caught signal, closing BDB database environment\n");
  if(db != NULL)
     bdb_close_env(db);
  exit(1);
}

int main(int argc, char** argv) {
                 
      if(argc != 4) {
        fprintf(stderr, "ERROR: usage: <db-env> <db-name> <servic_id> \n");
        exit(1);
      }


      db = bdb_open_env(argv[1], g_db_env_flags, argv[2], 
				DB_RDONLY);
      if(db == NULL) {
          fprintf(stderr, "ERROR: bdb_open failed \n");
          exit(1);
      }
      register_for_signals(close_db); 

      char buf[2400]; 
      int data_len = get_data(db,argv[3],buf, 2004,0);
      ssh_key_info_list* list = list_from_data(buf, data_len, SIGNATURE_LEN);
      if(list == NULL) {
        fprintf(stderr, "ERROR: Failed to parse message and create list of keys \n");
        exit(1);
      }
      print_key_info_list(stdout, list);
      printf("\n");
      free_key_info_list(list); 
      
      unsigned char *sig_ptr = (unsigned char*)buf + data_len - SIGNATURE_LEN; 

      BIO *bio, *b64;
      b64 = BIO_new(BIO_f_base64());
      bio = BIO_new_fp(stdout, BIO_NOCLOSE);
      bio = BIO_push(b64, bio);

      unsigned char der_header[22] = { 0x30, 0x81, 0xbf, 0x30, 0x0d, 0x06, 
		0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x04, 
		0x05, 0x00, 0x03, 0x81, 0xad, 0x00 };
      BIO_write(bio, der_header, 22);  		
      BIO_write(bio, sig_ptr, SIGNATURE_LEN);
      BIO_flush(bio);
      BIO_free_all(bio); 
      
      bdb_close_env(db);
      return 0;
}
