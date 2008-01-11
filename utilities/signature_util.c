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
void loop_over(DB *db, RSA* crypto_key, BOOL create_sig){
    DBC *cursorp;
    DBT key,data;
    int ret; 

    int count = 0;
    ret = db->cursor(db, NULL, &cursorp,0);
    if(ret) {
        printf("error opening cursor\n");
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
            int ret = get_signature(name_start, input_len, crypto_key,
                        sig_buf, &sig_len);
            if(ret || sig_len != SIGNATURE_LEN) {
                  DPRINTF(DEBUG_ERROR, "problem calculating sig \n");
                  continue;
            }

            ret = verify_signature(name_start, input_len, crypto_key,
                                      sig_buf, sig_len);
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
    printf("done examining %d entries \n", count);

    if(ret != DB_NOTFOUND) {
        printf("some error iterating through db: %s \n",
            db_strerror(ret));
        db->err(db, ret, "DB cursor");
    }

    if(cursorp != NULL)
      cursorp->close(cursorp);

}

DB *db; // global so signal handler can close db.

void close_db(int signal) {
  printf("Closing BDB database \n");
  if(db != NULL)
     bdb_close(db);
  exit(1);
}


int
main(int argc, char** argv)
{

      if(argc != 5) {
        printf("usage: <c|v> <db-env> <db-file> <key>\n");
        exit(1);
      }

      signal(SIGINT, close_db);

      RSA* key;
      BOOL create_keys = FALSE;
      if((argv[1][0] == 'c')) {
        create_keys = TRUE;
        key = load_private_key(argv[4]);
      } else 
        key = load_public_key(argv[4]);
      
      uint32_t env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB;
      uint32_t db_flags = DB_CREATE;
      db = bdb_open_env(argv[2], env_flags,
                    argv[3], db_flags);
      if(db == NULL) {
          printf("bdb_open failed \n");
          exit(1);
      }

      loop_over(db, key, create_keys);

      bdb_close(db);
      return 0;
}
