#ifndef STR_BUFFER_H_
#define STR_BUFFER_H_

#include <stdlib.h>
#include <string.h> 
#include <assert.h> 

/*
	This is an inefficient but simple append-only 
	dynamic string mechanism.  We should use this 
   	to replace all code where we currently allocate
	a fixed sized buffer and then fill it with string
	content.  
*/ 

typedef struct str_buffer_t { 
	char *str; 
	int len, max_len;
} str_buffer; 


static str_buffer* str_buffer_new(int start_size) { 
	str_buffer *b = (str_buffer*)malloc(sizeof(*b));
	b->len = 0;  
	assert(start_size >= 1); 
	b->max_len = start_size; 
	b->str = (char*)malloc(start_size);
	return b;  
} 

static void str_buffer_append(str_buffer *b, char* to_add) {
	int need = strlen(to_add);
	int have = b->max_len - b->len; 
	if (need > have) { 
		b->max_len = b->max_len + max(b->max_len,need); 
		b->str = (char*) realloc(b->str, b->max_len);  
	} 
	if(b->len) { 
		strcat(b->str,to_add);
		b->len += need; 
	} else {  
		// first append 
		strcpy(b->str, to_add); 
		b->len += (need + 1); // for NULL terminator
	} 
} 

static char *str_buffer_get(str_buffer *b) { 
	char *to_return = (char*)malloc(b->len); 
	strcpy(to_return,b->str); 
	return to_return; 
} 

static void str_buffer_free(str_buffer *b) { 
	free(b->str); 
	free(b); 
} 

#endif
