
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

void print_fingerprint(X509 * x);

int main(int argc, char **argv) {

  if(argc  != 2) {
    printf("usage: <pem-certificate> \n");
    exit(1); 
  }

  X509 *x=NULL;
  ENGINE *e = NULL;
  int informat = FORMAT_PEM;
  
  apps_startup();
	
  char *infile = argv[1]; 
  x=load_cert(bio_err,infile,informat,NULL,e,"Certificate");
  print_fingerprint(x); 

  return 0; 
}
