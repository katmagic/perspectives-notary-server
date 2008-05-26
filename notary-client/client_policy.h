#ifndef CLIENT_POLICY_H_
#define CLIENT_POLICY_H_

#include "notary_local.h"
#include "common.h"

BOOL check_quorum_duration(SSHNotary *notary, 
    char *key_data, uint16_t key_len, uint8_t key_type, 
    int quorum_size, uint32_t duration_sec, 
    uint32_t stale_limit_sec);

uint32_t get_quorum_duration(SSHNotary *notary, char *key_data, uint16_t key_len, 
    uint8_t key_type, int quorum_size, uint32_t stale_limit_sec, 
    BOOL *is_cur_consistent);

void print_policy_results(SSHNotary *notary, 
    char *key_data, uint16_t key_len,
    uint8_t key_type, int quorum_thresh,
    uint32_t required_duration, uint32_t stale_limit_sec, 
    BOOL is_cur_consistent, uint32_t quorum_duration);

#endif
