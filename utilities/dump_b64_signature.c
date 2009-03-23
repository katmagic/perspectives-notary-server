#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#include "db.h"
#include "common.h"
#include "notary_crypto.h"
#include "bdb_storage.h"
#include "notary_util.h"

unsigned int notary_debug = DEBUG_ERROR;

int main(int argc, char** argv) {
                 
      if(argc != 4) {
        printf("usage: <db-env> <db-name> <servic_id> \n");
        exit(1);
      }


      uint32_t env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB;
      DB *db = bdb_open_env(argv[1], env_flags, argv[2], DB_RDONLY);
      if(db == NULL) {
          printf("bdb_open failed \n");
          exit(1);
      }
      char buf[2400]; 
      int data_len = get_data(db,argv[3],buf, 2004);
      ssh_key_info_list* list = list_from_data(buf, data_len, SIGNATURE_LEN);
      if(list == NULL) {
        printf("Failed to parse message and create list of keys \n");
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
      
      bdb_close(db);
      return 0;
}
