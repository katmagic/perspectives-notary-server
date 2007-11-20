/* $OpenBSD: ssh.c,v 1.293 2006/08/03 03:34:42 deraadt Exp $ */
/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 * Ssh client program.  This program can be used to log into a remote machine.
 * The software supports strong authentication, encryption, and forwarding
 * of X11, TCP/IP, and authentication connections.
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 *
 * Copyright (c) 1999 Niels Provos.  All rights reserved.
 * Copyright (c) 2000, 2001, 2002, 2003 Markus Friedl.  All rights reserved.
 *
 * Modified to work with SSL by Niels Provos <provos@citi.umich.edu>
 * in Canada (German citizen).
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "includes.h"

#include <sys/types.h>
#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif
#include <sys/resource.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#ifdef HAVE_PATHS_H
#include <paths.h>
#endif
#include <pwd.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/evp.h>
#include <openssl/err.h>

#include "xmalloc.h"
#include "ssh.h"
#include "ssh1.h"
#include "ssh2.h"
#include "compat.h"
#include "cipher.h"
#include "packet.h"
#include "buffer.h"
#include "channels.h"
#include "key.h"
#include "authfd.h"
#include "authfile.h"
#include "pathnames.h"
#include "dispatch.h"
#include "clientloop.h"
#include "log.h"
#include "readconf.h"
#include "sshconnect.h"
#include "misc.h"
#include "kex.h"
#include "mac.h"
#include "sshpty.h"
#include "match.h"
#include "msg.h"
#include "monitor_fdpass.h"
#include "uidswap.h"
#include "version.h"

#ifdef SMARTCARD
#include "scard.h"
#endif

#include "mysql.h"
#include "mysql_storage.h"
#include "sys/wait.h"
#include "patricia.h"
#include "notary_util.h" // debugging only
#include "db.h"
#include "bdb_storage.h"
#include "notary_crypto.h"

extern char *__progname;

// hack for scanner
int long_jump_result;

unsigned int notary_debug = 0; //DEBUG_ERROR


/* Flag indicating whether debug mode is on.  This can be set on the command line. */
int debug_flag = 0;

/* Flag indicating whether a tty should be allocated */
int tty_flag = 0;
int no_tty_flag = 0;
int force_tty_flag = 0;

/* don't exec a shell */
int no_shell_flag = 0;

/*
 * Flag indicating that nothing should be read from stdin.  This can be set
 * on the command line.
 */
int stdin_null_flag = 0;

/*
 * Flag indicating that ssh should fork after authentication.  This is useful
 * so that the passphrase can be entered manually, and then ssh goes to the
 * background.
 */
int fork_after_authentication_flag = 0;

/*
 * General data structure for command line options and options configurable
 * in configuration files.  See readconf.h.
 */
Options options;

/* optional user configfile */
char *config = NULL;

/*
 * Name of the host we are connecting to.  This is the name given on the
 * command line, or the HostName specified for the user-supplied name in a
 * configuration file.
 */
char *host;

/* socket address the host resolves to */
struct sockaddr_storage hostaddr;

/* Private host keys. */
Sensitive sensitive_data;

/* Original real UID. */
uid_t original_real_uid;
uid_t original_effective_uid;

/* command to be executed */
Buffer command;

/* Should we execute a command or invoke a subsystem? */
int subsystem_flag = 0;

/* # of replies received for global requests */
static int client_global_request_id = 0;

/* pid of proxycommand child process */
pid_t proxy_command_pid = 0;

/* fd to control socket */
int control_fd = -1;

/* Multiplexing control command */
static u_int mux_command = 0;

/* Only used in control client mode */
volatile sig_atomic_t control_client_terminate = 0;
u_int control_server_pid = 0;

/* Prints a help message to the user.  This function never returns. */


static int ssh_session(void);
static int ssh_session2(void);
static void load_public_identity_files(void);
static void control_client(const char *path);

/*
 * Main program for the ssh client.
 */
int
do_ssh(char *host_str)
{
	int i, opt, exit_status;
	char *p, *cp, *line, buf[256];
	struct stat st;
	struct passwd *pw;
	int dummy;
	extern int optind, optreset;
	extern char *optarg;
	struct servent *sp;
	Forward fwd;

	/* Ensure that fds 0, 1 and 2 are open or directed to /dev/null */
	sanitise_stdfd();

	//__progname = ssh_get_progname(av[0]);
	init_rng();


	/* Get user data. */
	pw = getpwuid(original_real_uid);
	if (!pw) {
		logit("You don't exist, go away!");
		exit(255);
	}
	/* Take a copy of the returned structure. */
	pw = pwcopy(pw);

	initialize_options(&options);

	/* Parse command-line arguments. */
	host = host_str;

        /* Check that we got a host name. */
	if (!host)
          exit(1);

	SSLeay_add_all_algorithms();
	ERR_load_crypto_strings();

	/* Initialize the command to execute on remote host. */
	buffer_init(&command);


	/* Allocate a tty by default if no command specified. */
	if (buffer_len(&command) == 0)
		tty_flag = 1;

	/* Force no tty */
	if (no_tty_flag)
		tty_flag = 0;
	/* Do not allocate a tty if stdin is not a tty. */
	if ((!isatty(fileno(stdin)) || stdin_null_flag) && !force_tty_flag) {
		if (tty_flag)
			logit("Pseudo-terminal will not be allocated because stdin is not a terminal.");
		tty_flag = 0;
	}

	/*
	 * Initialize "log" output.  Since we are the client all output
	 * actually goes to stderr.
	 */
	log_init("ssh", options.log_level == -1 ? SYSLOG_LEVEL_INFO : options.log_level,
	    SYSLOG_FACILITY_USER, 1);

	/*
	 * Read per-user configuration file.  Ignore the system wide config
	 * file if the user specifies a config file on the command line.
	 */
	if (config != NULL) {
		if (!read_config_file(config, host, &options, 0))
			fatal("Can't open user config file %.100s: "
			    "%.100s", config, strerror(errno));
	} else  {
		snprintf(buf, sizeof buf, "%.100s/%.100s", pw->pw_dir,
		    _PATH_SSH_USER_CONFFILE);
		(void)read_config_file(buf, host, &options, 1);

		/* Read systemwide configuration file after use config. */
		(void)read_config_file(_PATH_HOST_CONFIG_FILE, host,
		    &options, 0);
	}

	/* Fill configuration defaults. */
	fill_default_options(&options);

	channel_set_af(options.address_family);

	/* reinit */
	log_init("ssh", options.log_level, SYSLOG_FACILITY_USER, 1);

	seed_rng();

	if (options.user == NULL)
		options.user = xstrdup(pw->pw_name);

	if (options.hostname != NULL)
		host = options.hostname;

	/* force lowercase for hostkey matching */
	if (options.host_key_alias != NULL) {
		for (p = options.host_key_alias; *p; p++)
			if (isupper(*p))
				*p = (char)tolower(*p);
	}

	/* Get default port if port has not been set. */
	if (options.port == 0) {
		sp = getservbyname(SSH_SERVICE_NAME, "tcp");
		options.port = sp ? ntohs(sp->s_port) : SSH_DEFAULT_PORT;
	}

	if (options.proxy_command != NULL &&
	    strcmp(options.proxy_command, "none") == 0)
		options.proxy_command = NULL;
	if (options.control_path != NULL &&
	    strcmp(options.control_path, "none") == 0)
		options.control_path = NULL;

	if (options.control_path != NULL) {
		char thishost[NI_MAXHOST];

		if (gethostname(thishost, sizeof(thishost)) == -1)
			fatal("gethostname: %s", strerror(errno));
		snprintf(buf, sizeof(buf), "%d", options.port);
		cp = tilde_expand_filename(options.control_path,
		    original_real_uid);
		options.control_path = percent_expand(cp, "p", buf, "h", host,
		    "r", options.user, "l", thishost, (char *)NULL);
		xfree(cp);
	}
	if (mux_command != 0 && options.control_path == NULL)
		fatal("No ControlPath specified for \"-O\" command");
	if (options.control_path != NULL)
		control_client(options.control_path);

	/* Open a connection to the remote host. */
	if (ssh_connect(host, &hostaddr, options.port,
	    options.address_family, options.connection_attempts,
#ifdef HAVE_CYGWIN
	    options.use_privileged_port,
#else
	    original_effective_uid == 0 && options.use_privileged_port,
#endif
	    options.proxy_command) != 0)
		exit(255);

	signal(SIGPIPE, SIG_IGN); /* ignore SIGPIPE early */

	/* Log into the remote system.  This never returns if the login fails. */
	ssh_login(&sensitive_data, host, (struct sockaddr *)&hostaddr, pw);

	/* We no longer need the private host keys.  Clear them now. */
	if (sensitive_data.nkeys != 0) {
		for (i = 0; i < sensitive_data.nkeys; i++) {
			if (sensitive_data.keys[i] != NULL) {
				/* Destroys contents safely */
				debug3("clear hostkey %d", i);
				key_free(sensitive_data.keys[i]);
				sensitive_data.keys[i] = NULL;
			}
		}
		xfree(sensitive_data.keys);
	}
	for (i = 0; i < options.num_identity_files; i++) {
		if (options.identity_files[i]) {
			xfree(options.identity_files[i]);
			options.identity_files[i] = NULL;
		}
		if (options.identity_keys[i]) {
			key_free(options.identity_keys[i]);
			options.identity_keys[i] = NULL;
		}
	}

	exit_status = compat20 ? ssh_session2() : ssh_session();
	packet_close();

	if (options.control_path != NULL && control_fd != -1)
		unlink(options.control_path);

	/*
	 * Send SIGHUP to proxy command if used. We don't wait() in
	 * case it hangs and instead rely on init to reap the child
	 */
	if (proxy_command_pid > 1)
		kill(proxy_command_pid, SIGHUP);

	return exit_status;
}

#define TIMEOUT 3
#define MAX_SIMULTANEOUS 256

typedef struct probe_info_t {
  pid_t pid;
  char *dns_name;
  int start_time;
} probe_info;

char *table_name;
int finished = 0;
int total = 0;
int successes = 0;
int from_db = 0;
my_bool db_empty = 0;
MYSQL_RES *result;
probe_info all_probes[MAX_SIMULTANEOUS];
MYSQL* mysql; // note: this is free for anyone to use
patricia_tree_t *not_valid;
DB* db;
RSA *priv_key;

void db_set_result(char *table_name) {

  MYSQL *mysql_alt = open_mysql_conn("localhost", 
            "root", "moosaysthecow", "ssh");
  char query_buf[128];
  snprintf(query_buf, 128, "SELECT dns_name from %s order by RAND()", 
                table_name);

  if(mysql_real_query(mysql_alt, query_buf, strlen(query_buf)) != 0) {
      fprintf(stderr, "Error querying %s for DNS names to probe: %s \n",
            table_name, mysql_error(mysql_alt));
            return;
  }

  // ugly.  i never release this DB connection 
  result = mysql_use_result(mysql_alt);
  if(!result) {
      mysql_free_result(result);
      close_mysql_conn(mysql_alt);
      exit(1);
  }
  
}

int createServerSocket() {
    int s, len;
    struct sockaddr_un local;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, "ssh_probe");
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }
    return s;
}

void handle_connection(int s, int cur_time) {
        int n = -1, t, s2;
        struct sockaddr_un remote;
        char buf[4048]; // bug: i had truncated keys b/c of this

        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
            perror("accept");
            exit(1);
        }

        int so_far = 0;
        while(n != 0) { 
          n = recv(s2, buf + so_far, 2048 - so_far, 0);
          if (n < 0){ 
            perror("recv");
            break;
          }
          so_far += n;
        } 
            
        int name_len = strlen(buf);
        char *version_str = buf + name_len + 1;
        int version_len = strlen(version_str);
        char *ptr = buf + name_len + version_len + 2;
        uint32_t ip_addr = *(uint32_t*)ptr;
        unsigned short port = *(unsigned short*) (ptr + 4);
        int key_type = *(int*) (ptr + 6);
        int key_len = so_far - name_len - version_len - 12;
        char *key_ptr = ptr + 10;
    
   //     Key *key = buf_to_key(key_ptr, key_len, key_type);
  //  key_write(key,stdout);
   // printf("\n");
    char name_buf[256];
    snprintf(name_buf,256,"%s:22",buf);
    
    printf("storing key len = %d for (%s) : \n", key_len, name_buf);

    record_observation(db, priv_key, name_buf, key_ptr, key_len,
                              key_type, cur_time);

     //only do this for the sake of my measurements
      store_ssh_probe_result(mysql, buf, port, ip_addr, 
          key_ptr, key_len, key_type, cur_time, version_str);  

        close(s2);

}



char *getNextName() {
    
    MYSQL_ROW row;
    if((row = mysql_fetch_row(result)) == NULL) {
      printf("!!!! DB EMPTY !!!!! \n");
      db_empty = 1;
      return NULL;
    }
    ++from_db;

    if(strcmp(table_name, "to_probe") == 0) {
      char buf[128];
      snprintf(buf,128,"'%s'",row[0]);
      delete_from(mysql,table_name, "dns_name",buf);
    }

    return strdup(row[0]);
        
       
      //   char buf[128];
      //   snprintf(buf,128,"'%s'",row[0]);
      //   int r = delete_from(mysql, "to_probe", "dns_name", buf);
      //   if(r != 1) {
      //      printf("unexecpted result from delete of %s \n", buf);
      //   }
         
}

int spawn_probe(int index) {

  while(!db_empty){
    all_probes[index].dns_name = getNextName();
    if(all_probes[index].dns_name == NULL) 
      continue;
    struct timeval t;
    gettimeofday(&t,NULL);
    
    pid_t pid = fork();

    if(pid == 0) {
    //  printf("child started for: %s \n", all_probes[index].dns_name);
      do_ssh(all_probes[index].dns_name);
        // no return
        // child exits within function
        printf("********** shouldn't happen ************* \n");
        exit(25);
    }
    all_probes[index].pid = pid;

    all_probes[index].start_time = t.tv_sec;
    return 1;
  }
  return 0;
}

void finished_process(int index) {

        all_probes[index].pid = 0;
        free(all_probes[index].dns_name);
        ++finished;
}

int main(int argc, char** argv) {


  if(argc != 2) {
      printf("usage: <mysql-table-name> \n");
      exit(1);
  }

  priv_key = load_private_key("private.pem");

  table_name = argv[1];
  mysql = open_mysql_conn("localhost", 
            "root", "moosaysthecow", "ssh");
 
  db_set_result(table_name);

  not_valid = New_Patricia(32);
  load_db_to_trie(not_valid, "exceptions");

  db = bdb_open("ssh.db", DB_CREATE);
  warm_db(db);

 // create UNIX domain server socket
 // to get replies from other threads
 int s = createServerSocket();

  while(finished < total || !db_empty){
    struct timeval now;
    gettimeofday(&now,NULL);
      

    for(int i = 0; i < MAX_SIMULTANEOUS; i++) {
    
      
      // handles initial probes
      if(all_probes[i].pid == 0) {
        if(spawn_probe(i))
          ++total;
        continue;
      }

      int status;
      pid_t p = waitpid(all_probes[i].pid, &status, WNOHANG);
      if(p > 0) {
          int code = -1;
          if(WIFEXITED(status)){
              code = WEXITSTATUS(status);
          }
              
         if(code == 8) 
           ++successes;
         else
          record_failure(mysql, all_probes[i].dns_name,now.tv_sec,code);
        finished_process(i);
        if(spawn_probe(i)) {
          ++total;

          if(total % 100 == 0) {
            printf("******** total = %d  successes = %d "
                "finished = %d  from-db = %d ******* \n", 
              total, successes, finished, from_db);
          }
        }
        continue;
      }else if(p < 0) {
        printf("error on wait for %d \n", all_probes[i].pid);
      }

      if(now.tv_sec > (all_probes[i].start_time + TIMEOUT)) {
     //   printf("timeout for: %s (child # %d)  \n", all_probes[i].dns_name , 
       //       all_probes[i].pid);
        kill(all_probes[i].pid, SIGKILL);
      }
    }
    fd_set readset;
    int result;
    struct timeval t;
    t.tv_sec = 2;
    t.tv_usec = 0;
      
    FD_ZERO(&readset);
    FD_SET(s, &readset);
    result = select(s + 1, &readset, NULL, NULL, &t); 

    if(result > 0) {
        if(FD_ISSET(s, &readset)) {
            handle_connection(s, now.tv_sec);
        }
      }else if(result < 0) {
          perror("select error: ");
    }
    
  }
  printf("All done with %d probes. %d keys found. \n", total, successes);
  Destroy_Patricia(not_valid, (void_fn1_t)NULL);
  mysql_close(mysql);
  bdb_close(db);
  return 0;
}


static void
ssh_init_forwarding(void)
{
	int success = 0;
	int i;

	/* Initiate local TCP/IP port forwardings. */
	for (i = 0; i < options.num_local_forwards; i++) {
		debug("Local connections to %.200s:%d forwarded to remote "
		    "address %.200s:%d",
		    (options.local_forwards[i].listen_host == NULL) ?
		    (options.gateway_ports ? "*" : "LOCALHOST") :
		    options.local_forwards[i].listen_host,
		    options.local_forwards[i].listen_port,
		    options.local_forwards[i].connect_host,
		    options.local_forwards[i].connect_port);
		success += channel_setup_local_fwd_listener(
		    options.local_forwards[i].listen_host,
		    options.local_forwards[i].listen_port,
		    options.local_forwards[i].connect_host,
		    options.local_forwards[i].connect_port,
		    options.gateway_ports);
	}
	if (i > 0 && success != i && options.exit_on_forward_failure)
		fatal("Could not request local forwarding.");
	if (i > 0 && success == 0)
		error("Could not request local forwarding.");

	/* Initiate remote TCP/IP port forwardings. */
	for (i = 0; i < options.num_remote_forwards; i++) {
		debug("Remote connections from %.200s:%d forwarded to "
		    "local address %.200s:%d",
		    (options.remote_forwards[i].listen_host == NULL) ?
		    "LOCALHOST" : options.remote_forwards[i].listen_host,
		    options.remote_forwards[i].listen_port,
		    options.remote_forwards[i].connect_host,
		    options.remote_forwards[i].connect_port);
		if (channel_request_remote_forwarding(
		    options.remote_forwards[i].listen_host,
		    options.remote_forwards[i].listen_port,
		    options.remote_forwards[i].connect_host,
		    options.remote_forwards[i].connect_port) < 0) {
			if (options.exit_on_forward_failure)
				fatal("Could not request remote forwarding.");
			else
				logit("Warning: Could not request remote "
				    "forwarding.");
		}
	}
}

static void
check_agent_present(void)
{
	if (options.forward_agent) {
		/* Clear agent forwarding if we don't have an agent. */
		if (!ssh_agent_present())
			options.forward_agent = 0;
	}
}

static int
ssh_session(void)
{
	int type;
	int interactive = 0;
	int have_tty = 0;
	struct winsize ws;
	char *cp;
	const char *display;

	/* Enable compression if requested. */
	if (options.compression) {
		debug("Requesting compression at level %d.", options.compression_level);

		if (options.compression_level < 1 || options.compression_level > 9)
			fatal("Compression level must be from 1 (fast) to 9 (slow, best).");

		/* Send the request. */
		packet_start(SSH_CMSG_REQUEST_COMPRESSION);
		packet_put_int(options.compression_level);
		packet_send();
		packet_write_wait();
		type = packet_read();
		if (type == SSH_SMSG_SUCCESS)
			packet_start_compression(options.compression_level);
		else if (type == SSH_SMSG_FAILURE)
			logit("Warning: Remote host refused compression.");
		else
			packet_disconnect("Protocol error waiting for compression response.");
	}
	/* Allocate a pseudo tty if appropriate. */
	if (tty_flag) {
		debug("Requesting pty.");

		/* Start the packet. */
		packet_start(SSH_CMSG_REQUEST_PTY);

		/* Store TERM in the packet.  There is no limit on the
		   length of the string. */
		cp = getenv("TERM");
		if (!cp)
			cp = "";
		packet_put_cstring(cp);

		/* Store window size in the packet. */
		if (ioctl(fileno(stdin), TIOCGWINSZ, &ws) < 0)
			memset(&ws, 0, sizeof(ws));
		packet_put_int((u_int)ws.ws_row);
		packet_put_int((u_int)ws.ws_col);
		packet_put_int((u_int)ws.ws_xpixel);
		packet_put_int((u_int)ws.ws_ypixel);

		/* Store tty modes in the packet. */
		tty_make_modes(fileno(stdin), NULL);

		/* Send the packet, and wait for it to leave. */
		packet_send();
		packet_write_wait();

		/* Read response from the server. */
		type = packet_read();
		if (type == SSH_SMSG_SUCCESS) {
			interactive = 1;
			have_tty = 1;
		} else if (type == SSH_SMSG_FAILURE)
			logit("Warning: Remote host failed or refused to allocate a pseudo tty.");
		else
			packet_disconnect("Protocol error waiting for pty request response.");
	}
	/* Request X11 forwarding if enabled and DISPLAY is set. */
	display = getenv("DISPLAY");
	if (options.forward_x11 && display != NULL) {
		char *proto, *data;
		/* Get reasonable local authentication information. */
		client_x11_get_proto(display, options.xauth_location,
		    options.forward_x11_trusted, &proto, &data);
		/* Request forwarding with authentication spoofing. */
		debug("Requesting X11 forwarding with authentication spoofing.");
		x11_request_forwarding_with_spoofing(0, display, proto, data);

		/* Read response from the server. */
		type = packet_read();
		if (type == SSH_SMSG_SUCCESS) {
			interactive = 1;
		} else if (type == SSH_SMSG_FAILURE) {
			logit("Warning: Remote host denied X11 forwarding.");
		} else {
			packet_disconnect("Protocol error waiting for X11 forwarding");
		}
	}
	/* Tell the packet module whether this is an interactive session. */
	packet_set_interactive(interactive);

	/* Request authentication agent forwarding if appropriate. */
	check_agent_present();

	if (options.forward_agent) {
		debug("Requesting authentication agent forwarding.");
		auth_request_forwarding();

		/* Read response from the server. */
		type = packet_read();
		packet_check_eom();
		if (type != SSH_SMSG_SUCCESS)
			logit("Warning: Remote host denied authentication agent forwarding.");
	}

	/* Initiate port forwardings. */
	ssh_init_forwarding();

	/* If requested, let ssh continue in the background. */
	if (fork_after_authentication_flag)
		if (daemon(1, 1) < 0)
			fatal("daemon() failed: %.200s", strerror(errno));

	/*
	 * If a command was specified on the command line, execute the
	 * command now. Otherwise request the server to start a shell.
	 */
	if (buffer_len(&command) > 0) {
		int len = buffer_len(&command);
		if (len > 900)
			len = 900;
		debug("Sending command: %.*s", len, (u_char *)buffer_ptr(&command));
		packet_start(SSH_CMSG_EXEC_CMD);
		packet_put_string(buffer_ptr(&command), buffer_len(&command));
		packet_send();
		packet_write_wait();
	} else {
		debug("Requesting shell.");
		packet_start(SSH_CMSG_EXEC_SHELL);
		packet_send();
		packet_write_wait();
	}

	/* Enter the interactive session. */
	return client_loop(have_tty, tty_flag ?
	    options.escape_char : SSH_ESCAPECHAR_NONE, 0);
}

static void
ssh_subsystem_reply(int type, u_int32_t seq, void *ctxt)
{
	int id, len;

	id = packet_get_int();
	len = buffer_len(&command);
	if (len > 900)
		len = 900;
	packet_check_eom();
	if (type == SSH2_MSG_CHANNEL_FAILURE)
		fatal("Request for subsystem '%.*s' failed on channel %d",
		    len, (u_char *)buffer_ptr(&command), id);
}

void
client_global_request_reply_fwd(int type, u_int32_t seq, void *ctxt)
{
	int i;

	i = client_global_request_id++;
	if (i >= options.num_remote_forwards)
		return;
	debug("remote forward %s for: listen %d, connect %s:%d",
	    type == SSH2_MSG_REQUEST_SUCCESS ? "success" : "failure",
	    options.remote_forwards[i].listen_port,
	    options.remote_forwards[i].connect_host,
	    options.remote_forwards[i].connect_port);
	if (type == SSH2_MSG_REQUEST_FAILURE) {
		if (options.exit_on_forward_failure)
			fatal("Error: remote port forwarding failed for "
			    "listen port %d",
			    options.remote_forwards[i].listen_port);
		else
			logit("Warning: remote port forwarding failed for "
			    "listen port %d",
			    options.remote_forwards[i].listen_port);
	}
}

static void
ssh_control_listener(void)
{
	struct sockaddr_un addr;
	mode_t old_umask;
	int addr_len;

	if (options.control_path == NULL ||
	    options.control_master == SSHCTL_MASTER_NO)
		return;

	debug("setting up multiplex master socket");

	memset(&addr, '\0', sizeof(addr));
	addr.sun_family = AF_UNIX;
	addr_len = offsetof(struct sockaddr_un, sun_path) +
	    strlen(options.control_path) + 1;

	if (strlcpy(addr.sun_path, options.control_path,
	    sizeof(addr.sun_path)) >= sizeof(addr.sun_path))
		fatal("ControlPath too long");

	if ((control_fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
		fatal("%s socket(): %s", __func__, strerror(errno));

	old_umask = umask(0177);
	if (bind(control_fd, (struct sockaddr *)&addr, addr_len) == -1) {
		control_fd = -1;
		if (errno == EINVAL || errno == EADDRINUSE)
			fatal("ControlSocket %s already exists",
			    options.control_path);
		else
			fatal("%s bind(): %s", __func__, strerror(errno));
	}
	umask(old_umask);

	if (listen(control_fd, 64) == -1)
		fatal("%s listen(): %s", __func__, strerror(errno));

	set_nonblock(control_fd);
}

/* request pty/x11/agent/tcpfwd/shell for channel */
static void
ssh_session2_setup(int id, void *arg)
{
	extern char **environ;
	const char *display;
	int interactive = tty_flag;

	display = getenv("DISPLAY");
	if (options.forward_x11 && display != NULL) {
		char *proto, *data;
		/* Get reasonable local authentication information. */
		client_x11_get_proto(display, options.xauth_location,
		    options.forward_x11_trusted, &proto, &data);
		/* Request forwarding with authentication spoofing. */
		debug("Requesting X11 forwarding with authentication spoofing.");
		x11_request_forwarding_with_spoofing(id, display, proto, data);
		interactive = 1;
		/* XXX wait for reply */
	}

	check_agent_present();
	if (options.forward_agent) {
		debug("Requesting authentication agent forwarding.");
		channel_request_start(id, "auth-agent-req@openssh.com", 0);
		packet_send();
	}

	if (options.tun_open != SSH_TUNMODE_NO) {
		Channel *c;
		int fd;

		debug("Requesting tun.");
		if ((fd = tun_open(options.tun_local,
		    options.tun_open)) >= 0) {
			c = channel_new("tun", SSH_CHANNEL_OPENING, fd, fd, -1,
			    CHAN_TCP_WINDOW_DEFAULT, CHAN_TCP_PACKET_DEFAULT,
			    0, "tun", 1);
			c->datagram = 1;
#if defined(SSH_TUN_FILTER)
			if (options.tun_open == SSH_TUNMODE_POINTOPOINT)
				channel_register_filter(c->self, sys_tun_infilter,
				    sys_tun_outfilter);
#endif
			packet_start(SSH2_MSG_CHANNEL_OPEN);
			packet_put_cstring("tun@openssh.com");
			packet_put_int(c->self);
			packet_put_int(c->local_window_max);
			packet_put_int(c->local_maxpacket);
			packet_put_int(options.tun_open);
			packet_put_int(options.tun_remote);
			packet_send();
		}
	}

	client_session2_setup(id, tty_flag, subsystem_flag, getenv("TERM"),
	    NULL, fileno(stdin), &command, environ, &ssh_subsystem_reply);

	packet_set_interactive(interactive);
}

/* open new channel for a session */
static int
ssh_session2_open(void)
{
	Channel *c;
	int window, packetmax, in, out, err;

	if (stdin_null_flag) {
		in = open(_PATH_DEVNULL, O_RDONLY);
	} else {
		in = dup(STDIN_FILENO);
	}
	out = dup(STDOUT_FILENO);
	err = dup(STDERR_FILENO);

	if (in < 0 || out < 0 || err < 0)
		fatal("dup() in/out/err failed");

	/* enable nonblocking unless tty */
	if (!isatty(in))
		set_nonblock(in);
	if (!isatty(out))
		set_nonblock(out);
	if (!isatty(err))
		set_nonblock(err);

	window = CHAN_SES_WINDOW_DEFAULT;
	packetmax = CHAN_SES_PACKET_DEFAULT;
	if (tty_flag) {
		window >>= 1;
		packetmax >>= 1;
	}
	c = channel_new(
	    "session", SSH_CHANNEL_OPENING, in, out, err,
	    window, packetmax, CHAN_EXTENDED_WRITE,
	    "client-session", /*nonblock*/0);

	debug3("ssh_session2_open: channel_new: %d", c->self);

	channel_send_open(c->self);
	if (!no_shell_flag)
		channel_register_confirm(c->self, ssh_session2_setup, NULL);

	return c->self;
}

static int
ssh_session2(void)
{
	int id = -1;

	/* XXX should be pre-session */
	ssh_init_forwarding();
	ssh_control_listener();

	if (!no_shell_flag || (datafellows & SSH_BUG_DUMMYCHAN))
		id = ssh_session2_open();

	/* Execute a local command */
	if (options.local_command != NULL &&
	    options.permit_local_command)
		ssh_local_cmd(options.local_command);

	/* If requested, let ssh continue in the background. */
	if (fork_after_authentication_flag)
		if (daemon(1, 1) < 0)
			fatal("daemon() failed: %.200s", strerror(errno));

	return client_loop(tty_flag, tty_flag ?
	    options.escape_char : SSH_ESCAPECHAR_NONE, id);
}

static void
load_public_identity_files(void)
{
	char *filename, *cp, thishost[NI_MAXHOST];
	int i = 0;
	Key *public;
	struct passwd *pw;
#ifdef SMARTCARD
	Key **keys;

	if (options.smartcard_device != NULL &&
	    options.num_identity_files < SSH_MAX_IDENTITY_FILES &&
	    (keys = sc_get_keys(options.smartcard_device, NULL)) != NULL) {
		int count = 0;
		for (i = 0; keys[i] != NULL; i++) {
			count++;
			memmove(&options.identity_files[1], &options.identity_files[0],
			    sizeof(char *) * (SSH_MAX_IDENTITY_FILES - 1));
			memmove(&options.identity_keys[1], &options.identity_keys[0],
			    sizeof(Key *) * (SSH_MAX_IDENTITY_FILES - 1));
			options.num_identity_files++;
			options.identity_keys[0] = keys[i];
			options.identity_files[0] = sc_get_key_label(keys[i]);
		}
		if (options.num_identity_files > SSH_MAX_IDENTITY_FILES)
			options.num_identity_files = SSH_MAX_IDENTITY_FILES;
		i = count;
		xfree(keys);
	}
#endif /* SMARTCARD */
	if ((pw = getpwuid(original_real_uid)) == NULL)
		fatal("load_public_identity_files: getpwuid failed");
	if (gethostname(thishost, sizeof(thishost)) == -1)
		fatal("load_public_identity_files: gethostname: %s",
		    strerror(errno));
	for (; i < options.num_identity_files; i++) {
		cp = tilde_expand_filename(options.identity_files[i],
		    original_real_uid);
		filename = percent_expand(cp, "d", pw->pw_dir,
		    "u", pw->pw_name, "l", thishost, "h", host,
		    "r", options.user, (char *)NULL);
		xfree(cp);
		public = key_load_public(filename, NULL);
		debug("identity file %s type %d", filename,
		    public ? public->type : -1);
		xfree(options.identity_files[i]);
		options.identity_files[i] = filename;
		options.identity_keys[i] = public;
	}
}

static void
control_client_sighandler(int signo)
{
	control_client_terminate = signo;
}

static void
control_client_sigrelay(int signo)
{
	if (control_server_pid > 1)
		kill(control_server_pid, signo);
}

static int
env_permitted(char *env)
{
	int i, ret;
	char name[1024], *cp;

	if ((cp = strchr(env, '=')) == NULL || cp == env)
		return (0);
	ret = snprintf(name, sizeof(name), "%.*s", (int)(cp - env), env);
	if (ret <= 0 || (size_t)ret >= sizeof(name))
		fatal("env_permitted: name '%.100s...' too long", env);

	for (i = 0; i < options.num_send_env; i++)
		if (match_pattern(name, options.send_env[i]))
			return (1);

	return (0);
}

static void
control_client(const char *path)
{
	struct sockaddr_un addr;
	int i, r, fd, sock, exitval, num_env, addr_len;
	Buffer m;
	char *term;
	extern char **environ;
	u_int  flags;

	if (mux_command == 0)
		mux_command = SSHMUX_COMMAND_OPEN;

	switch (options.control_master) {
	case SSHCTL_MASTER_AUTO:
	case SSHCTL_MASTER_AUTO_ASK:
		debug("auto-mux: Trying existing master");
		/* FALLTHROUGH */
	case SSHCTL_MASTER_NO:
		break;
	default:
		return;
	}

	memset(&addr, '\0', sizeof(addr));
	addr.sun_family = AF_UNIX;
	addr_len = offsetof(struct sockaddr_un, sun_path) +
	    strlen(path) + 1;

	if (strlcpy(addr.sun_path, path,
	    sizeof(addr.sun_path)) >= sizeof(addr.sun_path))
		fatal("ControlPath too long");

	if ((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
		fatal("%s socket(): %s", __func__, strerror(errno));

	if (connect(sock, (struct sockaddr *)&addr, addr_len) == -1) {
		if (mux_command != SSHMUX_COMMAND_OPEN) {
			fatal("Control socket connect(%.100s): %s", path,
			    strerror(errno));
		}
		if (errno == ENOENT)
			debug("Control socket \"%.100s\" does not exist", path);
		else {
			error("Control socket connect(%.100s): %s", path,
			    strerror(errno));
		}
		close(sock);
		return;
	}

	if (stdin_null_flag) {
		if ((fd = open(_PATH_DEVNULL, O_RDONLY)) == -1)
			fatal("open(/dev/null): %s", strerror(errno));
		if (dup2(fd, STDIN_FILENO) == -1)
			fatal("dup2: %s", strerror(errno));
		if (fd > STDERR_FILENO)
			close(fd);
	}

	term = getenv("TERM");

	flags = 0;
	if (tty_flag)
		flags |= SSHMUX_FLAG_TTY;
	if (subsystem_flag)
		flags |= SSHMUX_FLAG_SUBSYS;
	if (options.forward_x11)
		flags |= SSHMUX_FLAG_X11_FWD;
	if (options.forward_agent)
		flags |= SSHMUX_FLAG_AGENT_FWD;

	buffer_init(&m);

	/* Send our command to server */
	buffer_put_int(&m, mux_command);
	buffer_put_int(&m, flags);
	if (ssh_msg_send(sock, SSHMUX_VER, &m) == -1)
		fatal("%s: msg_send", __func__);
	buffer_clear(&m);

	/* Get authorisation status and PID of controlee */
	if (ssh_msg_recv(sock, &m) == -1)
		fatal("%s: msg_recv", __func__);
	if (buffer_get_char(&m) != SSHMUX_VER)
		fatal("%s: wrong version", __func__);
	if (buffer_get_int(&m) != 1)
		fatal("Connection to master denied");
	control_server_pid = buffer_get_int(&m);

	buffer_clear(&m);

	switch (mux_command) {
	case SSHMUX_COMMAND_ALIVE_CHECK:
		fprintf(stderr, "Master running (pid=%d)\r\n",
		    control_server_pid);
		exit(0);
	case SSHMUX_COMMAND_TERMINATE:
		fprintf(stderr, "Exit request sent.\r\n");
		exit(0);
	case SSHMUX_COMMAND_OPEN:
		/* continue below */
		break;
	default:
		fatal("silly mux_command %d", mux_command);
	}

	/* SSHMUX_COMMAND_OPEN */
	buffer_put_cstring(&m, term ? term : "");
	buffer_append(&command, "\0", 1);
	buffer_put_cstring(&m, buffer_ptr(&command));

	if (options.num_send_env == 0 || environ == NULL) {
		buffer_put_int(&m, 0);
	} else {
		/* Pass environment */
		num_env = 0;
		for (i = 0; environ[i] != NULL; i++)
			if (env_permitted(environ[i]))
				num_env++; /* Count */

		buffer_put_int(&m, num_env);

		for (i = 0; environ[i] != NULL && num_env >= 0; i++)
			if (env_permitted(environ[i])) {
				num_env--;
				buffer_put_cstring(&m, environ[i]);
			}
	}

	if (ssh_msg_send(sock, SSHMUX_VER, &m) == -1)
		fatal("%s: msg_send", __func__);

	mm_send_fd(sock, STDIN_FILENO);
	mm_send_fd(sock, STDOUT_FILENO);
	mm_send_fd(sock, STDERR_FILENO);

	/* Wait for reply, so master has a chance to gather ttymodes */
	buffer_clear(&m);
	if (ssh_msg_recv(sock, &m) == -1)
		fatal("%s: msg_recv", __func__);
	if (buffer_get_char(&m) != SSHMUX_VER)
		fatal("%s: wrong version", __func__);
	buffer_free(&m);

	signal(SIGHUP, control_client_sighandler);
	signal(SIGINT, control_client_sighandler);
	signal(SIGTERM, control_client_sighandler);
	signal(SIGWINCH, control_client_sigrelay);

	if (tty_flag)
		enter_raw_mode();

	/* Stick around until the controlee closes the client_fd */
	exitval = 0;
	for (;!control_client_terminate;) {
		r = read(sock, &exitval, sizeof(exitval));
		if (r == 0) {
			debug2("Received EOF from master");
			break;
		}
		if (r > 0)
			debug2("Received exit status from master %d", exitval);
		if (r == -1 && errno != EINTR)
			fatal("%s: read %s", __func__, strerror(errno));
	}

	if (control_client_terminate)
		debug2("Exiting on signal %d", control_client_terminate);

	close(sock);

	leave_raw_mode();

	if (tty_flag && options.log_level != SYSLOG_LEVEL_QUIET)
		fprintf(stderr, "Connection to master closed.\r\n");

	exit(exitval);
}
