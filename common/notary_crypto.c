
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/md5.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"


RSA* load_private_key(char *filename) {

  EVP_PKEY *priv_key = NULL;
  BIO *priv_key_bio = BIO_new(BIO_s_file());
  if(BIO_read_filename(priv_key_bio, filename) <= 0){
      printf("Error opening '%s' \n", filename);
      return NULL;
  }
  priv_key = PEM_read_bio_PrivateKey(priv_key_bio, NULL,
                                           NULL, NULL);
  if(!priv_key) {
      printf("priv_key is null\n");
      return NULL;
  }
  BIO_free(priv_key_bio);
  RSA *rsa = EVP_PKEY_get1_RSA(priv_key);
  EVP_PKEY_free(priv_key);
  return rsa;
}

RSA* load_public_key(char *filename) {

  EVP_PKEY *pub_key = NULL;
  BIO *pub_key_bio = BIO_new(BIO_s_file());
  if(BIO_read_filename(pub_key_bio, filename) <= 0){
      printf("Error opening '%s' \n",filename);
      return NULL;
  }
  pub_key = PEM_read_bio_PUBKEY(pub_key_bio, NULL,
                                           NULL, NULL);
  if(!pub_key) {
      printf("pub_key is null\n");
      return NULL;
  }
  RSA *rsa = EVP_PKEY_get1_RSA(pub_key);
  EVP_PKEY_free(pub_key);
  return rsa;
}


 
int get_signature(char *buf, unsigned int buf_size, 
                     RSA *priv_key,
                     unsigned char *sig_buf, unsigned int *sig_len) {

  
  unsigned char digest[16];
  unsigned int digest_len = 16;
  MD5_CTX md5;
  MD5_Init(&md5);
  MD5_Update(&md5, (unsigned char*)buf, buf_size);
  MD5_Final(digest, &md5);

  int ret_val = RSA_sign(NID_md5, digest, digest_len, 
      sig_buf, sig_len, priv_key);
  if(!ret_val) {
      char buf[128];
      unsigned long e = ERR_get_error();
      ERR_error_string(e, buf);
      printf("signing error: %s \n", buf);
      return 1;
  }
 
  return 0;
}

int verify_signature(char *buf, unsigned int buf_size, 
                      RSA *pub_key, 
                     unsigned char *sig_buf, unsigned int sig_len) {


  unsigned char digest[16];
  unsigned int digest_len = 16;
  MD5_CTX md5;
  MD5_Init(&md5);
  MD5_Update(&md5, (unsigned char*)buf, buf_size);
  MD5_Final(digest, &md5);
  
  int ret_val = RSA_verify(NID_md5,digest, digest_len, 
            sig_buf, sig_len, pub_key);

  return ret_val;
}

int verify_message_signature(notary_header *hdr, RSA* pub_key) {
    
    int sig_len = ntohs(hdr->sig_len);
    int data_len = ntohs(hdr->total_len) - sig_len - sizeof(notary_header);
    char* data = (char*)(hdr + 1);
    unsigned char *sig = (unsigned char*) (data + data_len);
    DPRINTF(DEBUG_CRYPTO, "msg verify: data_len = %d sig_len = %d \n",
          data_len, sig_len);
    return verify_signature(data, data_len, pub_key, sig, sig_len);
}


/*
int main(int argc, char** argv) {

  RSA *priv_key = load_private_key("private.pem");
  RSA *pub_key = load_public_key("public.pem");

  if(priv_key == NULL || pub_key == NULL)
    return 1;

  printf("loaded a priv-key of size = %d \n", RSA_size(priv_key));
  printf("loaded a pub-key of size = %d \n", RSA_size(pub_key));

  unsigned char *string = (unsigned char*)"your mom ate my lunch!";
  
  unsigned char *sig_buf = malloc(RSA_size(priv_key));
  unsigned int sig_len;
  unsigned int data_len = (unsigned int)strlen((char*)string);

  int ret = get_signature((notary_header*)string, data_len, priv_key, 
                                  sig_buf, &sig_len);
  if(ret) return 1;

  verify_signature((notary_header*)string, data_len, pub_key,
                                     sig_buf, sig_len);

  printf("string: %s \n", string);
  return 0;

}
*/
