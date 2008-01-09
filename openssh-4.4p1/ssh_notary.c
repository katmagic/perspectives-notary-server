#include "includes.h"
#include "xmalloc.h"
#include <stdlib.h>
#include "pathnames.h"
#include "key.h"

#include "notary_util.h"
#include "notary_local.h"
#include "ssh_notary.h"
#include "common.h"
#include "client_policy.h"
#include "contact_notary.h" 

// this is cruft from 'misc.h', as there seem
// to be problems #include-ing it
#define RP_ECHO                 0x0001
#define RP_ALLOW_STDIN          0x0002
#define RP_ALLOW_EOF            0x0004
#define RP_USE_ASKPASS          0x0008

char    *read_passphrase(const char *, int);
char     *tilde_expand_filename(const char *, uid_t);

#define _PATH_NOTARY_LIST	"~/.ssh/notary_list.txt"
#define _PATH_NOTARY_CLIENT_CONFIG	"~/.ssh/client_params.txt"
#define NUM_RETRIES 3

unsigned int notary_debug = DEBUG_ERROR; 

// if there is a security error, or the user has requested to always be
// prompted, we ask the user whether they want to see Notary details 
int view_prompt()
{
	const char *msg = "View detailed notary results? 'no' (default), 'yes', or 'abort':";
	char *p;
	int ret = - 1;

	p = read_passphrase(msg, RP_ECHO);
	if (p && (p[0] == 'y' || p[0] == 'Y'))
		ret = NOTARY_PROMPT_VIEW;
	else if(p && strncasecmp(p, "abort", 4) == 0)
		ret = 2;
	if (p)
		xfree(p);
	if(ret == -1) return NOTARY_PROMPT_SKIP;

	if(ret == 2) exit(1);

	return ret;
}

void do_probe_check(char* hostname, int port, 
		Key* host_key, int original_real_uid, int needsPrompt) {
        uint8_t *digest;
        uint32_t digest_len;

        digest = key_fingerprint_raw(host_key, SSH_FP_MD5,&digest_len);
        if(digest == NULL) {
          DPRINTF(DEBUG_ERROR,"Notary client could not parse key\n"); 
          exit(1);
        }
        uint8_t key_type = host_key->type; 

	DPRINTF(DEBUG_INFO, "checking key of type: %s \n", 
            keytype_2_str(key_type));
	
	char *notary_list_fname = tilde_expand_filename(
                       _PATH_NOTARY_LIST,original_real_uid);
	char* client_config_fname = tilde_expand_filename(
                    _PATH_NOTARY_CLIENT_CONFIG,original_real_uid);
	
        client_config conf;
        parse_client_config(&conf, client_config_fname);
        if(conf.debug) {
          printf("turning on debug output from config option \n"); 
          notary_debug = DEBUG_ERROR | DEBUG_INFO; 
        }

        Notary *notary = init_ssh_notary();
	load_notary_server_file(notary, notary_list_fname);

	printf("contacting notaries....\n");
	fflush(stdout);
	
        //TODO: fix, for really long dns-names, we should actually 
        //be truncating the dns-name, not the port + service-type. 
        char service_info[MAX_NAME_LEN];
        snprintf(service_info,MAX_NAME_LEN,"%s:%d,%d", 
                            hostname, port, SERVICE_TYPE_SSH); 

        fetch_notary_observations(notary, service_info, 
                      (int)conf.timeout_secs, NUM_RETRIES); 

        int status;
        int max_stale_sec = (int)DAY2SEC(conf.max_stale_days); 
        uint32_t quorum_duration = get_quorum_duration(notary, 
                                       (char*)digest, (int)digest_len, 
                                       key_type, conf.quorum,
                                       max_stale_sec, &status); 

        float qd_days = SEC2DAY(quorum_duration); 
	BOOL warn = FALSE;
        if(status) {
          printf("WARNGING: Your key cannot be authenticated because \n"
                 "no Notary replies were received.\n"
                 "This may be because you do not have full Internet \n"
                 "connectivity or because all notaries are down.\n"
                 "It could also be an attacker preventing you from \n"
                 "reaching the Notaries.  Proceed with caution. \n"); 
        }else if(qd_days > conf.quorum_duration_days) {
          // key satisfies quorum duration.  it should be safe
          printf("This key has been consistently seen for the past %.1f days\n", qd_days); 
        }else if(quorum_duration > 0) {
          warn = TRUE; 
          // key has quorum, but not sufficient duration 
          printf("WARNING: Server key has been seen consistently for only the past %.1f days \n", qd_days); 
        } else {
          warn = TRUE; 
          // key does not even achieve quorum
          printf("SUSPECTED ATTACK: The offered key is NOT consistent.\n"); 
          // TODO: print out how many notaries do see it
        }
	
	if(needsPrompt || warn) { 
		int result = view_prompt();
		if(result == NOTARY_PROMPT_VIEW) {
                  char* hex = buf_2_hexstr((char*)digest,(int)digest_len); 
                  printf("Offered Key = %s '%s' \n", 
                      keytype_2_str(key_type) , hex); 
                  print_notary_reply(stdout, notary) ;
                  free(hex); 
		}
	}

// end_label:

//	if(warn) 
//		connect = continue_prompt();

//	return connect;
}

