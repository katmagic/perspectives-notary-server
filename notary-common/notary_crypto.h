#ifndef NOTARY_CRYPTO_H_
#define NOTARY_CRYPTO_H_

#include "common.h"
#include <openssl/rsa.h>

char *base64(const unsigned char *input, int length);

RSA *key_from_buf(char *buf, int len, BOOL is_private);
RSA* load_private_key(char *filename);
RSA* load_public_key(char *filename);
int get_signature(char *hdr, unsigned int hdr_size, 
                     RSA *priv_key,
                     unsigned char *sig_buf, unsigned int *sig_len);

int verify_signature(char *hdr, unsigned int hdr_size, 
                      RSA *pub_key, 
                     unsigned char *sig_buf, unsigned int sig_len);
int verify_message_signature(notary_header *hdr, RSA* pub_key);

int get_signature_rsa_sha256(char *hdr, unsigned int hdr_size, 
                     RSA *priv_key,
                     unsigned char *sig_buf, unsigned int *sig_len);
int verify_signature_rsa_sha256(char *hdr, unsigned int hdr_size, 
                      RSA *pub_key, 
                     unsigned char *sig_buf, unsigned int sig_len);

#endif
