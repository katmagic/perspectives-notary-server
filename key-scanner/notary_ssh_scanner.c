
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>

#include "patricia.h"
#include "db.h"
#include "bdb_storage.h"
#include "notary_crypto.h"
#include "flex_queue.h"
#include "notary_util.h"
#include "notary_ssh_scanner.h"

unsigned int notary_debug = DEBUG_ALL;

#define FINISHED_CHILD_SOCK_NAME "ssh_probe_finished"


// function used by spawned client processes to report resulting key back to
// the main scanner process.  called from sshconnect.c
void record_key(char *dns_name, uint32_t ip_addr, uint16_t port, Key *key,
                  char *server_version_string){

    int s, len;
    struct sockaddr_un remote;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    uint8_t *digest;
    uint32_t digest_len;

    digest = key_fingerprint_raw(key, SSH_FP_MD5,&digest_len);
    if(digest == NULL) {
        exit(29); // special exit code
    }

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, FINISHED_CHILD_SOCK_NAME);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    int name_len = strlen(dns_name);
   /* char* key_buf;
    int key_len = 0;
    key_to_buf(key, &key_buf, &key_len);
    if(key_buf == NULL){ 
        printf("Failed to convert key to data buffer \n");
        exit(10);
    }
    */

    int version_len = strlen(server_version_string);

    int total_len = name_len +  digest_len 
          + version_len + 12; // ip-addr, port, key_type, null-byte X 2 = 12
    char * buf = (char*)malloc(total_len);
    char *ptr = buf;
    memcpy(ptr, dns_name, name_len + 1);
    ptr += name_len + 1;
    memcpy(ptr, server_version_string, version_len + 1);
    ptr += version_len + 1;
    memcpy(ptr, &ip_addr, 4);
    ptr += 4;
    memcpy(ptr, &port, 2);
    ptr += 2;
    memcpy(ptr, &key->type, 4);
    ptr += 4;
    memcpy(ptr, digest, digest_len);

    int n = send(s, buf,total_len , 0);
    if(n == -1) {
       perror("send");
       exit(1);
    }

    free(digest);
    free(buf);
    close(s);
}


// read in name-value pairs from file to specify config
// parameters for the scanner 
void parse_config_file(scanner_config *conf, char* fname){
	char buf[1024];
	FILE *f;
	assert(fname);

	f = fopen(fname, "r");
	if(f == NULL) {
		fprintf(stderr,
		"Notary Error: Invalid conf file %s \n", fname);
		return;
	}

	while(fgets(buf, 1023,f) != NULL) {
		if(*buf == '\n') continue;
		if(*buf == '#') continue;
		int size = strlen(buf);
		buf[size - 1] = 0x0; // replace '\n' with NULL
		char *delim = strchr(buf,'=');
		if(delim == NULL) {
			DPRINTF(DEBUG_ERROR, 
				"Ignoring malformed line: %s \n", buf);
			continue;
		}
		*delim = 0x0;
	 
		char *value = delim + 1;
		DPRINTF(DEBUG_INFO, "key = '%s' value = '%s' \n", 
				buf, value);
		if(strcmp(buf,"input_fname") == 0) { 
			conf->input_fname = strdup(value);
		} else if(strcmp(buf, "output_fname") == 0) {
			conf->output_fname = strdup(value);
		} else if(strcmp(buf, "db_env_fname") == 0){
			conf->db_env_fname = strdup(value);
		} else if(strcmp(buf, "private_key_fname") == 0){
			conf->private_key_fname = strdup(value);
		} else if(strcmp(buf, "db_fname") == 0) {
			conf->db_fname = strdup(value);
		} else if(strcmp(buf, "exceptions_fname") == 0) {
			conf->exceptions_fname = strdup(value);
		} else {
			DPRINTF(DEBUG_ERROR, "Unknown config value %s : %s \n",
					buf, value);
		}
	}		
}






int do_ssh(char *host_str);

#define TIMEOUT 3
#define MAX_SIMULTANEOUS 256


int finished = 0;
int total = 0;
int successes = 0;
int from_db = 0;

probe_info all_probes[MAX_SIMULTANEOUS];
patricia_tree_t *not_valid;
DB* db;
RSA *priv_key;


int createClientFinishedSocket() {
    int s, len;
    struct sockaddr_un local;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, FINISHED_CHILD_SOCK_NAME);
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
    DPRINTF(DEBUG_INFO, "Listening for finished children on sock = %d \n",s);
    return s;
}

void handle_finished_client(int s, int cur_time) {
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
        //uint32_t ip_addr = *(uint32_t*)ptr;
        unsigned short port = *(unsigned short*) (ptr + 4);
        int key_type = *(int*) (ptr + 6);
        int key_len = so_far - name_len - version_len - 12;
        char *key_ptr = ptr + 10;
    
    char name_buf[256];
    snprintf(name_buf,256,"%s:%d",buf, port);
    
    char *str = buf_2_hexstr((char*)key_ptr, key_len);
    DPRINTF(DEBUG_INFO, "'%s' has %s key: '%s' \n", name_buf, 
          key_type_str(key_type), str); 
    free(str);
/*
    record_observation(db, priv_key, name_buf, key_ptr, key_len,
                              key_type, cur_time);
*/
    close(s2);

}


flex_queue *load_from_file(char *fname){ 

        char buf[1024];
	FILE *f;
	assert(fname);

	f = fopen(fname, "r");
	if(f == NULL) {
		DPRINTF(DEBUG_ERROR,"invalid to_probe file %s \n", fname);
		exit(1);
	}
	flex_queue* q = queue_init(30, sizeof(char*));
	while(fgets(buf, 1024,f) != NULL) {
		if(*buf == '\n') continue;
		int size = strlen(buf);
		buf[size - 1] = 0x0; // replace '\n' with NULL
                char *copy = strdup(buf);
                DPRINTF(DEBUG_INFO, "Loaded service-id = '%s'\n",copy);
                queue_pushback(q,(char*)&copy);
	}		

        DPRINTF(DEBUG_INFO, "Loaded %d service-ids \n", 
                queue_size(q));
        return q;
}

void spawn_probe(int index, flex_queue *queue, uint32_t now) {
    queue_popfront(queue, (char*)&(all_probes[index].dns_name));
   
    DPRINTF(DEBUG_INFO, "Forking child for: %s \n",
          all_probes[index].dns_name);
    pid_t pid = fork();

    if(pid == 0) {
        DPRINTF(DEBUG_INFO, "Hello from child: %s \n",
          all_probes[index].dns_name);
        do_ssh(all_probes[index].dns_name);
        // no return
        // child exits within function
        printf("********** shouldn't happen ************* \n");
        exit(25);
    }
    // parent continues here
    all_probes[index].pid = pid;
    all_probes[index].start_time = now;
}

// checks if the child has exited, or if it has timed-out
// and we need to kill it.  
// sets probe's pid to 0 if the child is finished 
void check_probe_progress(probe_info *probe, uint32_t now) {

      int status;
      pid_t p = waitpid(probe->pid, &status, WNOHANG);
      if(p > 0) {
          if(WIFEXITED(status)) {
              int code = WEXITSTATUS(status);
              if(code == 8) 
                ++successes;
              else {
                DPRINTF(DEBUG_INFO, "Child Error: exit code = %d for '%s'\n",
                    code, probe->dns_name);
              }
          } else if(WIFSIGNALED(status)) {
              int signal = WTERMSIG(status);
              if(signal == SIGKILL){ 
                DPRINTF(DEBUG_INFO, "Timeout for '%s' \n", probe->dns_name);
              } else {
                DPRINTF(DEBUG_ERROR, "Unexpected signal = %d for '%s'",
                    signal, probe->dns_name);
              }
          } else {
              DPRINTF(DEBUG_ERROR, "child neither exited, nor was signaled \n");
          }
              
          probe->pid = 0; 
          free(probe->dns_name);
          return;
      }else if(p < 0) {
        printf("error on wait for %d \n", probe->pid);
      }

      // check if we should timeout this child 
      if(now > (probe->start_time + TIMEOUT)) {
        //   printf("timeout for: %s (child # %d)  \n", 
        //   all_probes[i].dns_name , all_probes[i].pid);
        kill(probe->pid, SIGKILL);
        // note: we kill it here, but we don't set probe->pid = 0
        // because we wait for the indication of a child's 
        // exit via waitpid
      }
}


void check_client_finished_socket(int sock, uint32_t now) {
    fd_set readset;
    int result;
    struct timeval t;
    t.tv_sec = 2;
    t.tv_usec = 0;
      
    FD_ZERO(&readset);
    FD_SET(sock, &readset);
    result = select(sock + 1, &readset, NULL, NULL, &t); 

    if(result > 0) {
        if(FD_ISSET(sock, &readset)) {
            handle_finished_client(sock, now);
        }
      }else if(result < 0) {
          perror("select error: ");
    }
    
}


int main(int argc, char** argv) {


  if(argc != 3) {
      printf("usage: <conf-file> <probe-file> \n");
      exit(1);
  }

  scanner_config config;
  parse_config_file(&config, argv[1]);

  priv_key = load_private_key(config.private_key_fname);

  not_valid = New_Patricia(32);
  load_file_to_trie(not_valid, config.exceptions_fname);

  uint32_t env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB;
  uint32_t db_flags = DB_CREATE;
  db = bdb_open_env(config.db_env_fname, env_flags,
                    config.db_fname, db_flags);
  warm_db(db);

   // create UNIX domain server socket
   // to get replies from other threads
   int client_finished_sock = createClientFinishedSocket();
  
  flex_queue *to_probe = load_from_file(argv[2]);

  struct timeval now;
  gettimeofday(&now,NULL);
  BOOL is_done = FALSE;
    
  printf("spawning initial probes \n");
  // spawn initial probes
  for(int i = 0; i < MAX_SIMULTANEOUS; i++) {
      if(queue_size(to_probe) == 0) {
        is_done = TRUE;
        break;
      }
      spawn_probe(i, to_probe, now.tv_sec);
      ++total;
  }
  printf("done spawning initial probes \n");

  while(finished < total || !is_done){
    gettimeofday(&now,NULL);
      
    for(int i = 0; i < MAX_SIMULTANEOUS; i++) {
      probe_info *probe = &all_probes[i];
      if(probe->pid == 0) continue;

      check_probe_progress(probe, now.tv_sec); 
      
      if(probe->pid == 0) {

        if(queue_size(to_probe) > 0) {
          spawn_probe(i, to_probe, now.tv_sec);
          ++total;
        }else {
          is_done = TRUE;
        }
        ++finished;
        if(finished % 100 == 0) {
            printf("******** total spawned = %d  finished = %d "
                "successes = %d ******* \n",  total, finished, successes);
        }

      }
    } // end for 
    check_client_finished_socket(client_finished_sock, now.tv_sec);
  } // end while

  printf("All done with %d probes. %d keys found. \n", total, successes);
  Destroy_Patricia(not_valid, (void_fn1_t)NULL);
  bdb_close(db);
  return 0;
}
