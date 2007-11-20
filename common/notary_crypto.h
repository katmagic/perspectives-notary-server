#ifndef NOTARY_CRYPTO_H_
#define NOTARY_CRYPTO_H_

#include <openssl/rsa.h>

RSA* load_private_key(char *filename);
RSA* load_public_key(char *filename);
int get_signature(char *hdr, unsigned int hdr_size, 
                     RSA *priv_key,
                     unsigned char *sig_buf, unsigned int *sig_len);

int verify_signature(char *hdr, unsigned int hdr_size, 
                      RSA *pub_key, 
                     unsigned char *sig_buf, unsigned int sig_len);
int verify_message_signature(notary_header *hdr, RSA* pub_key);

#endif
