
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>

//#include "patricia.h"
#include "db.h"
#include "bdb_storage.h"
#include "notary_crypto.h"
#include "flex_queue.h"
#include "notary_util.h"
#include "notary_scanner.h"
#include "keyscan_util.h"
#include "net_util.h"

unsigned int notary_debug = DEBUG_ERROR;
//unsigned int notary_debug = DEBUG_INFO | DEBUG_ERROR;

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
		} else if(strcmp(buf, "max_simultaneous") == 0) {
			conf->max_simultaneous = atoi(value);
		} else {
			DPRINTF(DEBUG_ERROR, "Unknown config value %s : %s \n",
					buf, value);
		}
	}		
}

#define TIMEOUT 3
#define DO_SIGNATURE TRUE

int finished = 0;
int total = 0;
int successes = 0;

probe_info *all_probes;
//patricia_tree_t *not_valid;
DB* db;
RSA *priv_key;

int child_finished_sock;
int new_request_sock;
flex_queue *to_probe; 


void handle_finished_client(int cur_time) {
        
        char buf[4048]; // bug: i had truncated keys b/c of this
        int data_len = readUnixClientData(child_finished_sock, buf, 4048); 
        if(data_len == -1) {
          DPRINTF(DEBUG_ERROR, "Read from finished client failed \n"); 
          return; 
        }

        int name_len = strlen(buf);
        char *version_str = buf + name_len + 1;
        int version_len = strlen(version_str);
        char *ptr = buf + name_len + version_len + 2;
        //uint32_t ip_addr = *(uint32_t*)ptr;
        //unsigned short port = *(unsigned short*) (ptr + 4);
        int key_type = *(int*) (ptr + 6);
        int key_len = data_len - name_len - version_len - 12;
        if(key_len != KEY_LEN) {
          DPRINTF(DEBUG_ERROR, "Finished client gave odd key-len = %d \n",
              key_len); 
          return; 
        }
        char *key_ptr = ptr + 10;
    
        char *str = buf_2_hexstr((char*)key_ptr, key_len);
        DPRINTF(DEBUG_INFO, "'%s' has %s key: '%s' \n", buf, 
            keytype_2_str(key_type), str); 
        free(str);
        
        record_observation(db, priv_key, buf, key_ptr, key_len,
                              key_type, cur_time, DO_SIGNATURE);
    
}


void load_from_file(flex_queue *to_probe, char *fname){ 

        char buf[1024];
	FILE *f;
	assert(fname);

	f = fopen(fname, "r");
	if(f == NULL) {
		DPRINTF(DEBUG_ERROR,"invalid to_probe file %s \n", fname);
		exit(1);
	}
	while(fgets(buf, 1024,f) != NULL) {
		if(*buf == '\n') continue;
		int size = strlen(buf);
		buf[size - 1] = 0x0; // replace '\n' with NULL
                char *copy = strdup(buf);
                DPRINTF(DEBUG_INFO, "Loaded service-id = '%s'\n",copy);
                queue_pushback(to_probe,(char*)&copy);
	}		

        DPRINTF(DEBUG_INFO, "Loaded %d service-ids \n", 
                queue_size(to_probe));
}


char* ssh_args[] = { "ssh", "fill in", NULL }; 
char *ssl_args[] = { "openssl", "s_client", "-connect", "fill in", NULL}; 

void spawn_probe(int index, flex_queue *queue, uint32_t now) {
    queue_popfront(queue, (char*)&(all_probes[index].dns_name));
   
    DPRINTF(DEBUG_INFO, "Forking child for: %s \n",
          all_probes[index].dns_name);
    pid_t pid = fork();

    if(pid == 0) {
        DPRINTF(DEBUG_INFO, "Hello from child: %s \n",
          all_probes[index].dns_name);
        
        char *host_and_port = all_probes[index].dns_name; 
        char *comma = strchr(host_and_port,','); 
        if(comma == NULL) {
          DPRINTF(DEBUG_ERROR,"malformed, no comma in string\n");
          exit(2); 
        }
        *(comma) = 0;
        int service_type = atoi(comma + 1); 
        if(service_type == SERVICE_TYPE_SSH) {
          ssh_args[1] = host_and_port;
          execv(/*"./empty"*/"../ssh-scanner/ssh"/**/, ssh_args); 
        } else if(service_type == SERVICE_TYPE_SSL) {
          ssl_args[3] = host_and_port;
          execv("../ssl-scanner/apps/openssl", ssl_args); 
        }else {
          DPRINTF(DEBUG_ERROR, "Invalid service-type: %d \n", 
              service_type);
          exit(3); 
        }
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
        printf("error on wait for %d (waitpid returned %d) \n", 
            probe->pid, p);
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

void add_probe_request() {

}


void check_server_sockets(uint32_t now) {

    fd_set readset;
    int result;
    struct timeval t;
    t.tv_sec = 2;
    t.tv_usec = 0;
      
    FD_ZERO(&readset);
    FD_SET(child_finished_sock, &readset);
    FD_SET(new_request_sock, &readset);
    int max = (child_finished_sock > new_request_sock) ? 
		child_finished_sock + 1 : new_request_sock + 1; 
    result = select(max, &readset, NULL, NULL, &t); 

    if(result > 0) {
        if(FD_ISSET(child_finished_sock, &readset)) {
            handle_finished_client(now);
        }
        if(FD_ISSET(new_request_sock, &readset)) {
            add_probe_request(); 
        }
      }else if(result < 0) {
          perror("select error: ");
    }
    
}


int main(int argc, char** argv) {


  if(argc != 3 && argc != 2) {
      printf("usage: <conf-file> [probe-file] \n");
      exit(1);
  }

  
  scanner_config config;
  parse_config_file(&config, argv[1]);

  priv_key = load_private_key(config.private_key_fname);

  all_probes = (probe_info*)calloc(config.max_simultaneous, sizeof(probe_info)); 

  //not_valid = New_Patricia(32);
  //load_file_to_trie(not_valid, config.exceptions_fname);

  uint32_t env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB;
  uint32_t db_flags = DB_CREATE;
  db = bdb_open_env(config.db_env_fname, env_flags,
                    config.db_fname, db_flags);
  warm_db(db);

   // create global UNIX domain server sockets
   // to get replies from other threads
  child_finished_sock = openUnixServerSock(FINISHED_CHILD_SOCK_NAME );
  new_request_sock = openUnixServerSock(NEW_REQUEST_SOCK_NAME);  
 
  to_probe = queue_init(30, sizeof(char*));
  if(argc == 3) 
    load_from_file(to_probe, argv[2]);

  struct timeval start;
  gettimeofday(&start,NULL);
  BOOL is_done = FALSE;
    
  printf("spawning initial probes \n");
  // spawn initial probes
  for(int i = 0; i < config.max_simultaneous; i++) {
      if(queue_size(to_probe) == 0) {
        is_done = TRUE;
        break;
      }
      spawn_probe(i, to_probe, start.tv_sec);
      ++total;
  }
  printf("done spawning initial probes \n");

  struct timeval now;
  while(finished < total || !is_done){
    gettimeofday(&now,NULL);
      
    for(int i = 0; i < config.max_simultaneous; i++) {
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
    
    gettimeofday(&now,NULL);
    float since_start = TIMEVAL_DIFF_MILLIS(now,start) / 1000;
    float finish_rate = ((float)finished/since_start); 
    float success_rate = ((float)successes/finished); 
    printf("finish_rate = %0.3f with %0.2f success \n", finish_rate, success_rate); 

    // see if a child has reported back, or 
    // if we have received a new probe request
    check_server_sockets(now.tv_sec);
  } // end while

  printf("All done with %d probes. %d keys found. \n", total, successes);
  //Destroy_Patricia(not_valid, (void_fn1_t)NULL);
  bdb_close(db);
  return 0;
}
