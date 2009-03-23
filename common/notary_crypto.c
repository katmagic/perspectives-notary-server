
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/md5.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>


char *base64(const unsigned char *input, int length)
{
	BIO *bmem, *b64;
	BUF_MEM *bptr;

	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	BIO_write(b64, input, length);
	BIO_flush(b64);
	BIO_get_mem_ptr(b64, &bptr);

	char *buff = (char *)malloc(bptr->length);
	memcpy(buff, bptr->data, bptr->length-1);
	buff[bptr->length-1] = 0;

	BIO_free_all(b64);
	return buff;
}



int read_key_file(char *filename, char *buf, int max_len) {
  FILE* f = fopen(filename, "r");

  size_t bytes = fread(buf, 1, max_len ,f); 
  if(ferror(f)){ 
    perror("file open");
    exit(1);
  }

  if(!feof(f)) {
    DPRINTF(DEBUG_ERROR, "Unable to read full file "
          " with key buffer of size %d \n", max_len);
    exit(1);
  }

  return bytes;

}



RSA* key_from_bio(BIO *key_bio, BOOL is_private) {

  EVP_PKEY *pkey = NULL;
  
  if(is_private) {
    pkey = PEM_read_bio_PrivateKey(key_bio, 
                          NULL,NULL, NULL);
  }else {
    pkey = PEM_read_bio_PUBKEY(key_bio, NULL,
                                        NULL, NULL);
  }
  if(!pkey) {
      printf("key read from BIO is null\n");
      exit(1);
  }
  BIO_free(key_bio);
  RSA *rsa = EVP_PKEY_get1_RSA(pkey);
  EVP_PKEY_free(pkey);
  return rsa;
}

RSA *key_from_buf(char *buf, int len, BOOL is_private) {
  BIO *key_bio = BIO_new_mem_buf(buf, len);
  return key_from_bio(key_bio, is_private);
}

RSA* load_private_key(char *filename) {
  char buf[5000];
  int len = read_key_file(filename, buf, 5000);
  return key_from_buf(buf,len,TRUE);
}

RSA* load_public_key(char *filename) {
  char buf[5000];
  int len = read_key_file(filename, buf, 5000);
  return key_from_buf(buf,len, FALSE);
}


// computes an RSA-MD5 signature over 'buf' using 'priv_key'
// signature data is returned is 'sig_buf' which should be at least
// SIGNATURE_LEN bytes in size.  
// Method returns 0 on success.   
int get_signature(char *buf, unsigned int buf_size, RSA *priv_key,
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
      unsigned long e = ERR_get_error();
      DPRINTF(DEBUG_ERROR,"RSA_sign error: %s", ERR_error_string(e, buf));
      return 1;
  }
 
  return 0;
}

// verifies a RSA-MD5 signature 'sig_buf' of data 'buf' for signing key
// 'pub_key'.  Returns 1 if the signature if valid, 0 otherwise.  
int verify_signature(char *buf, unsigned int buf_size, RSA *pub_key, 
                     unsigned char *sig_buf, unsigned int sig_len) {


  unsigned char digest[16];
  unsigned int digest_len = 16;
  MD5_CTX md5;
  MD5_Init(&md5);
  MD5_Update(&md5, (unsigned char*)buf, buf_size);
  MD5_Final(digest, &md5);
  
  return RSA_verify(NID_md5,digest, digest_len,sig_buf, sig_len, pub_key);
}

// computes an RSA-SHA256 signature over 'buf' using 'priv_key'
// signature data is returned is 'sig_buf' which should be at least
// SIGNATURE_LEN bytes in size.  
// Method returns 0 on success.   
int get_signature_rsa_sha256(char *buf, unsigned int buf_size, RSA *priv_key,
                   unsigned char *sig_buf, unsigned int *sig_len) {

  unsigned char digest[32];
  unsigned int digest_len = 32;
  SHA256_CTX ctx;
  SHA256_Init(&ctx);
  SHA256_Update(&ctx, (unsigned char*)buf, buf_size);
  SHA256_Final(digest, &ctx);

  int ret_val = RSA_sign(NID_sha256, digest, digest_len, 
			sig_buf, sig_len, priv_key);
  if(!ret_val) {
      unsigned long e = ERR_get_error();
      DPRINTF(DEBUG_ERROR,"RSA_sign error: %s", ERR_error_string(e, buf));
      return 1;
  }
 
  return 0;
}

// verifies a RSA-SHA256 signature 'sig_buf' of data 'buf' for signing key
// 'pub_key'.  Returns 1 if the signature if valid, 0 otherwise.  
int verify_signature_rsa_sha256(char *buf, unsigned int buf_size, RSA *pub_key, 
                     unsigned char *sig_buf, unsigned int sig_len) {

  unsigned char digest[32];
  unsigned int digest_len = 32;
  SHA256_CTX ctx;
  SHA256_Init(&ctx);
  SHA256_Update(&ctx, (unsigned char*)buf, buf_size);
  SHA256_Final(digest, &ctx);

  return RSA_verify(NID_sha256,digest, digest_len,sig_buf, sig_len, pub_key);
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
