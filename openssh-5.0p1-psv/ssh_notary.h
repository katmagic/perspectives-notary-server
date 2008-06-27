#ifndef _SSH_NOTARY_H_
#define _SSH_NOTARY_H_

#define NOTARY_PROMPT_VIEW 0
#define NOTARY_PROMPT_SKIP 1

void do_probe_check(char* hostname, int port, Key* host_key, int original_real_uid,
		int needsPrompt, Key *cached_key);
int notary_prompt();

#endif