#include "includes.h"
#include "xmalloc.h"
#include <stdlib.h>
#include <math.h> 
#include "pathnames.h"
#include "key.h"

#include "net_util.h"
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


void print_cached_key_info(SSHNotary *notary, Key *cached_key) { 
	if(!cached_key)
		return;

        uint8_t *digest;
        uint32_t digest_len;
        digest = key_fingerprint_raw(cached_key, SSH_FP_MD5,&digest_len);

        if(digest == NULL) {
          DPRINTF(DEBUG_ERROR,"Notary client could not parse cached key\n"); 
          return; 
        }
        uint8_t key_type = cached_key->type; 
	uint32_t last_end = most_recent_sighting(notary, digest,
					digest_len, key_type); 
	if(last_end == 0) { 
		printf("CACHED KEY INFO: cached key has not been observed by any notaries\n"); 
	} 
        struct timeval now;
        gettimeofday(&now, NULL);
	float len_in_days = SEC2DAY(now.tv_sec - last_end);  
	printf("CACHED KEY INFO: cached key was last observed by a notaries %.2f days ago\n",
								len_in_days); 
} 


void do_probe_check(char* hostname, int port, 
		Key* host_key, int original_real_uid, int needsPrompt, 
		Key* cached_key) {
        uint8_t *digest;
        uint32_t digest_len;
 	
	// don't contact notaries if client entered in an RFC 1918 address
 	// note: if they enter in a DNS name, we still want to probe even
	// if that name resolves to RFC 1918, since DNS can be spoofed.
   	// In the future, we should print a different warning in that case
  	// though.  
	if( is_rfc1918(hostname) ) { 
	   printf("Skipping notary query for RFC 1918 hostname: %s \n", 
							     hostname);  
	   return; 
	}  

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
          notary_debug = DEBUG_ERROR | DEBUG_INFO | DEBUG_POLICY; 
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
	
	print_cached_key_info(notary, cached_key);

        BOOL is_cur_consistent;
        int max_stale_sec = (int)DAY2SEC(conf.max_stale_days);

        // how many notaries do we need for quorum? 
        int notaries_contacted = (conf.num_notaries == -1) ?  
                        get_number_of_notaries(notary) : conf.num_notaries; 
        int notaries_required = (int)ceil(conf.quorum * ((float)notaries_contacted));
          
        uint32_t quorum_duration = get_quorum_duration(notary, 
                                       (char*)digest, (int)digest_len, 
                                       key_type, notaries_required,
                                       max_stale_sec, &is_cur_consistent); 

        float qd_days = SEC2DAY(quorum_duration);
        DPRINTF(DEBUG_POLICY,"quorum-duration = %f days (consistent = %d )\n", 
                                                    qd_days, is_cur_consistent); 
	BOOL warn = FALSE;
        if(!is_cur_consistent) {
          warn = TRUE; 
          // key does not even achieve quorum
          fprintf(stderr,"SUSPECTED ATTACK: The offered key is NOT consistent.\n"); 
          // TODO: print out how many notaries do see it
        }else if(qd_days > conf.quorum_duration_days) {
          // key satisfies quorum duration.  it should be safe
          fprintf(stderr,"This key has been consistently seen for the past %.1f days\n", qd_days); 
        }else if (qd_days < 0.1) {
          warn = TRUE; 
          // key has quorum, but is brand new 
          fprintf(stderr,"WARNING: Key is currently consistent, but has no key history \n"); 
        } else  {
          warn = TRUE; 
          // key has quorum, but not sufficient duration 
          fprintf(stderr,"WARNING: Key is consistent, but has been seen only for the past %.1f days \n", qd_days); 
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

