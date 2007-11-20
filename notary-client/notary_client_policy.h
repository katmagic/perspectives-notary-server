#ifndef NOTARY_CLIENT_POLICY_H_
#define NOTARY_CLIENT_POLICY_H_

#include "notary_local.h"

int getMostRecentConflict(SSHNotary *notary, Key* host_key);
int getOldestCorrectSighting(SSHNotary *notary, Key* host_key);
int getMostStaleProbe(SSHNotary *notary);


void check_key_consistency(SSHNotary *notary, Key* host_key, int* consistency_len,
		BOOL* sawInconsistency);

#endif
