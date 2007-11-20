#ifndef _NOTARY_UTIL_H_
#define _NOTARY_UTIL_H_

#define NOTARY_PROMPT_VIEW 0
#define NOTARY_PROMPT_SKIP 1

#include "key.h"

void do_probe_check(char* hostname, int port, Key* host_key, int original_real_uid,
		int needsPrompt);
int notary_prompt();

#endif
