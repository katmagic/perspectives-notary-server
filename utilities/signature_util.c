#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "db.h"
#include "common.h"
#include "notary_crypto.h"
#include "notary_util.h"
#include "bdb_storage.h"

unsigned int notary_debug = DEBUG_ERROR;
// if 'create' is true, then 'key' is a private key
// and we will regenerate all DB entries.  
// otherwise, 'key' is a public key and we just verify all entries
void loop_over(DB *db, RSA* crypto_key, BOOL create_sig, char* sig_type){
    DBC *cursorp;
    DBT key,data;
    int ret; 

    int count = 0;
    ret = db->cursor(db, NULL, &cursorp,0);
    if(ret) {
        fprintf(stderr, "ERROR: error opening cursor\n");
        db->err(db, ret, "Cursor open: ");
        exit(1);
    }

    char buf[MAX_PACKET_LEN];
    char *name_start = buf + sizeof(notary_header);
    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));
    while((ret = cursorp->get(cursorp,&key,&data, DB_NEXT)) == 0) {
        memcpy(name_start, key.data, key.size);
        memcpy(name_start + key.size, data.data, data.size);
        notary_header *hdr = (notary_header*)buf;
        hdr->total_len = htons(sizeof(notary_header) + key.size
                                    + data.size);
        hdr->sig_len = htons(SIGNATURE_LEN);

        if(create_sig) {
            int input_len = key.size + data.size - SIGNATURE_LEN;
            unsigned int sig_len = -1;
            unsigned char sig_buf[SIGNATURE_LEN];
            int ret = 0; 
	    if(strcmp(sig_type,"sha256") == 0) { 
		ret = get_signature_rsa_sha256(name_start, input_len, 
			crypto_key, sig_buf, &sig_len);
	    } else { 
		ret = get_signature(name_start, input_len, crypto_key,
                        sig_buf, &sig_len);
	    } 
            if(ret || sig_len != SIGNATURE_LEN) {
                  DPRINTF(DEBUG_ERROR, "problem calculating sig \n");
                  continue;
            }

	    if(strcmp(sig_type,"sha256") == 0) { 
            	ret = verify_signature_rsa_sha256(name_start, input_len, 
			crypto_key, sig_buf, sig_len);
            } else {
		ret = verify_signature(name_start, input_len, crypto_key,
                                      sig_buf, sig_len);
	    }
            if(ret){ 
              char *sig_start = name_start + input_len;
              memcpy(sig_start, sig_buf, sig_len);
            
              // Store the resulting changes.
              // Need to separate the data (ssh_key_info structs
              // plus signature) from the key (host and port string) 
              char *data_start = name_start + key.size;
              int data_len = data.size;
              DPRINTF(DEBUG_CRYPTO, "Storing new data: name = %s data-len"
                              " = %d\n", name_start, data_len);
              store_data(db, name_start, data_start, data_len);

            } else { 
              DPRINTF(DEBUG_ERROR, "sig calculation failed \n");
            }
        } else {
          // the user only asked us to verify the signature
          if(!verify_message_signature(hdr,crypto_key)){
            DPRINTF(DEBUG_ERROR, "***** Sig Invalid : %s **** \n", 
                            (char*) key.data);
          }
       }
        
        ++count;
    }
    fprintf(stderr, "INFO: done examining %d entries \n", count);

    if(ret != DB_NOTFOUND) {
        fprintf(stderr, "ERROR: some error iterating through db: %s \n",
            db_strerror(ret));
        db->err(db, ret, "ERROR: DB cursor");
    }

    if(cursorp != NULL)
      cursorp->close(cursorp);

}

DB *db; // global so signal handler can close db.

void close_db(int signal) {
  fprintf(stderr, "WARNING: Caught signal, closing BDB database environment\n");
  if(db != NULL)
     bdb_close_env(db);
  exit(1);
}


int
main(int argc, char** argv)
{

      if(argc != 6) {
        fprintf(stderr, "ERROR: usage: <c|v> <db-env> <db-file> <key> <md5|sha256>\n");
        exit(1);
      }

      register_for_signals(close_db); 

      RSA* key;
      BOOL create_keys = FALSE;
      if((argv[1][0] == 'c')) {
        create_keys = TRUE;
        key = load_private_key(argv[4]);
      } else 
        key = load_public_key(argv[4]);
      
      db = bdb_open_env(argv[2], g_db_env_flags,
                    argv[3], DB_CREATE);
      if(db == NULL) {
          fprintf(stderr, "ERROR: bdb_open failed \n");
          exit(1);
      }

      loop_over(db, key, create_keys, argv[5]);

      bdb_close_env(db);
      return 0;
}
