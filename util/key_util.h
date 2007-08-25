

#include "../common.h"
#include "key.h"
#include "buffer.h"

// caller must free mememory in buf
static void key_to_buf(Key *key, char** buf, int* buf_len) {

        if(key->type == KEY_RSA1) {
		// dw: there's likely a better way to do this
		Buffer msg;
		buffer_init(&msg);
		buffer_put_int(&msg, BN_num_bits(key->rsa->n));
		buffer_put_bignum(&msg, key->rsa->e);
		buffer_put_bignum(&msg, key->rsa->n);

		*buf_len = buffer_len(&msg);

		*buf = (char*)malloc(*buf_len);
		memcpy(*buf, msg.buf, *buf_len);
		buffer_free(&msg);
		
        }else if (key->type == KEY_RSA || key->type == KEY_DSA) {
                key_to_blob(key, (u_char**)buf, (u_int*) buf_len);
        }else {
             fprintf(stderr, "invalid type %d for key %x \n", 
                 key->type, (unsigned int)key);
             *buf = NULL;
             *buf_len = -1;
        }  
}

static Key *buf_to_key(char* buf, int buf_len, int key_type) {

	if(key_type == KEY_RSA1) {
		Buffer msg;
		buffer_init(&msg);
		buffer_append(&msg, buf, (u_int)buf_len);

        	(void) buffer_get_int(&msg); // ignored

		Key *key = key_new(KEY_RSA1);
	        buffer_get_bignum(&msg, key->rsa->e);
        	buffer_get_bignum(&msg, key->rsa->n);
		return key;
		
	} else {
		return key_from_blob((u_char*)buf, buf_len);
	}

}
