#include "includes.h"
#include "../common.h"
#include "xmalloc.h"
#include <stdlib.h>
#include "ssh_notary.h"
#include "pathnames.h"
#include "notary_local.h"
#include "key.h"


// this is cruft from 'misc.h', as there seem
// to be problems #include-ing it
#define RP_ECHO                 0x0001
#define RP_ALLOW_STDIN          0x0002
#define RP_ALLOW_EOF            0x0004
#define RP_USE_ASKPASS          0x0008

char    *read_passphrase(const char *, int);
char     *tilde_expand_filename(const char *, uid_t);


#define STALE_THRESHOLD_SEC (60 * 10) // ten minutes

/*

int continue_prompt()
{
	const char *msg = "Do you wish to connect? 'no' (default), 'yes':";
	char *p;
	int ret = FALSE;

	p = read_passphrase(msg, RP_ECHO);
	if (p && (p[0] == 'y' || p[0] == 'Y'))
		ret = TRUE;
	if (p)
		xfree(p);

	return ret;
}
*/

int view_prompt()
{
	const char *msg = "View Probing Details? 'no' (default), 'yes', or 'abort':";
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

	char *cert_file = tilde_expand_filename(_PATH_NOTARY_PROBE_SERVER_CERT,
		 original_real_uid);
	char* server_file = tilde_expand_filename(_PATH_NOTARY_PROBE_SERVERS,
		 original_real_uid);
	SSHNotary *notary = init_ssh_notary(cert_file);
	load_probe_servers(notary, server_file);
	printf("contacting probing servers.... ");
	contact_probe_servers(notary, 0, hostname, host_key->type, port);
	printf("Probe Results: \n");

	int last_conflict = getMostRecentConflict(notary, host_key);
	int oldest_correct = getOldestCorrectSighting(notary,host_key);
	int most_stale = getMostStaleProbe(notary);


	BOOL warn = FALSE;
	if(last_conflict == -1 && oldest_correct == -1) {
		printf("No probe server returned useful results\n");
		warn = TRUE;
		return;
	}
	
	struct timeval t;
	gettimeofday(&t,NULL);
	int cur_secs = t.tv_sec;
//	BOOL connect = TRUE;

	int stale_diff = cur_secs - most_stale;
	if(stale_diff > STALE_THRESHOLD_SEC) {
		printf("********* Stale Probe Warning ******* \n");
		printf("At least one server has not probed '%s' in %.1f minutes \n",
				hostname, SEC2MIN(stale_diff));
		warn = TRUE;
	}

	if(last_conflict == -1) {
		int first_diff = cur_secs - oldest_correct;
		printf("No inconsistent keys seen (oldest probe from %.1f days ago)\n"
			, SEC2DAY(first_diff));
	}else {
		int conflict_diff = cur_secs - last_conflict;
		if(conflict_diff < STALE_THRESHOLD_SEC) {
			printf("******* Warning ***********\n");
			printf("Inconsisent keys observed within last %.1f minutes \n",
				SEC2MIN(conflict_diff));	
			warn = TRUE;
		} else {
			printf("The key is consistent across all servers\n");
			printf("Last inconsistent keys seen %0.1f days ago\n", SEC2DAY(conflict_diff));
		}
	}
	if(needsPrompt || warn) { 
		int result = view_prompt();
		if(result == NOTARY_PROMPT_VIEW) {
			printf("Probe used certificate file '%s'\n", cert_file);
			printf("Probe used server-info file '%s'\n", server_file);
			print_probe_info(notary);
		}
	}

// end_label:

//	if(warn) 
//		connect = continue_prompt();

//	return connect;
}

