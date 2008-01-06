
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef OPENSSL_NO_STDIO
#define APPS_WIN16
#endif
#include "apps.h"
#include <openssl/bio.h>
#include <openssl/asn1.h>
#include <openssl/err.h>
#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/objects.h>
#include <openssl/pem.h>
#ifndef OPENSSL_NO_RSA
#include <openssl/rsa.h>
#endif
#ifndef OPENSSL_NO_DSA
#include <openssl/dsa.h>
#endif



/*
char * buf_2_hexstr(char *dgst_raw, int dgst_raw_len){

	char *retval;
	u_int i;

        int str_len = dgst_raw_len * 3 + 1;
	retval = malloc(str_len);
        bzero(retval, str_len);
	for (i = 0; i < dgst_raw_len; i++) {
		char hex[4];
		snprintf(hex, sizeof(hex), "%02x:", (u_char)dgst_raw[i]);
		strncat(retval, hex, dgst_raw_len * 3 + 1);
	}

	retval[(dgst_raw_len * 3) - 1] = '\0';
	return retval;
}
*/

unsigned int notary_debug = 0; // no debug 

#include "notary_util.h" 
#include "keyscan_util.h"

void ssl_record_key(char *host, unsigned short port, X509 * x) {
  
  int j;
  unsigned int n;
  unsigned char md[EVP_MAX_MD_SIZE];
  
  const EVP_MD *digest=EVP_sha1();
  const EVP_MD *md_alg = EVP_get_digestbyname("md5"); 
  digest = md_alg; 

  BIO* bio_err=BIO_new_fp(stderr,BIO_NOCLOSE);

  if (!X509_digest(x,digest,md,&n))
  {
    BIO_printf(bio_err,"out of memory\n");
    exit(19);
  }

  record_key(host, 0, port, md, n, SSL_ANY, "unknown-ssl",
      SERVICE_TYPE_SSL); 
/*
  char *str = buf_2_hexstr(md, n); 
  printf("MD5 fingerprint: %s \n", str); 
  free(str); 
*/

}



