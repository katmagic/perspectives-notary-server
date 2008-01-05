#ifndef CLIENT_POLICY_H_
#define CLIENT_POLICY_H_

#include "notary_local.h"
#include "common.h"

BOOL check_quorum_duration(SSHNotary *notary, char *key_data, uint16_t key_len, uint8_t key_type, 
                                    int quorum_size, uint32_t duration_sec, 
                                    uint32_t stale_limit_sec);

uint32_t get_quorum_duration(SSHNotary *notary, char *key_data, uint16_t key_len, uint8_t key_type, 
                                    int quorum_size, uint32_t stale_limit_sec, int *status);

#endif
