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
#include "notary_util.h"

/*
 Note: this file is mainly for debugging mozilla signature
 verification. At some point, we may integrate this into an
 an HTTP notary server so that it returns mozilla compatible 
 signatures (but i'd prefer we just do that in javascript). 
*/


unsigned int notary_debug = DEBUG_ERROR;

int
main(int argc, char** argv)
{

      if(argc != 3) {
        printf("usage: <private-key> <string-to-sign>\n");
        exit(1);
      }

      RSA* key = load_private_key(argv[1]);
      unsigned int sig_len = -1;
      unsigned char sig_buf[SIGNATURE_LEN];
      int ret = get_signature(argv[2],strlen(argv[2]),key, sig_buf,&sig_len);
      if(ret) { 
	fprintf(stderr,"Error generating signature\n"); 
        return 1; 
      }
      BIO *bio, *b64;
      b64 = BIO_new(BIO_f_base64());
      bio = BIO_new_fp(stdout, BIO_NOCLOSE);
      bio = BIO_push(b64, bio);

      char der_header[22] = { 0x30, 0x81, 0xbf, 0x30, 0x0d, 0x06, 0x09, 
		0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x04, 
		0x05, 0x00, 0x03, 0x81, 0xad, 0x00 };
      BIO_write(bio, der_header, 22);  			
      BIO_write(bio, sig_buf, sig_len);
      BIO_flush(bio);
      BIO_free_all(bio); 
      return 0;
}
