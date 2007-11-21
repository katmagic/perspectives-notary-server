
#include "ares.h"
#include "ares_dns.h"
#include "inet_ntop.h"
#include "inet_net_pton.h"

#include "mysql_storage.h"
#include "net_util.h"
#include "debug.h"

ares_channel channel;
int requests_outstanding;
int total_recorded;
MYSQL* mysql_global;

int dns_init() {
  int status;
  struct ares_options opts;
  opts.timeout = 4;
  opts.tries = 3;  // we rarely need to try three times, so why not
  int opt_mask = (ARES_OPT_TIMEOUT | ARES_OPT_TRIES);
  status = ares_init_options(&channel, &opts, opt_mask);

  if (status != ARES_SUCCESS)
    {
      DPRINTF(DEBUG_ERROR, "ares_init_opt: %s\n", ares_strerror(status));
      return 1;
    }
   return 0;
}


void dns_batch_loop() {
  int nfds;
  fd_set read_fds, write_fds;
  struct timeval *tvp, tv;

  FD_ZERO(&read_fds);
  FD_ZERO(&write_fds);
  nfds = ares_fds(channel, &read_fds, &write_fds);
  if (nfds == 0)
     return;
  tvp = ares_timeout(channel, NULL, &tv);
  select(nfds, &read_fds, &write_fds, NULL, tvp);
  ares_process(channel, &read_fds, &write_fds);
}


// does IP to name, then name to IP to confirm
static void ip_2_name_callback(void *arg, int status, struct hostent *host);
static void name_2_ip_callback(void *arg, int status, struct hostent *host);

static void ip_2_name_callback(void *arg, int status, struct hostent *host){

  uint32_t ip_addr = *(uint32_t*)arg;

  if (status != ARES_SUCCESS || host == NULL){
//       printf("Reverse look-up failed for: %s \n", ip_2_str(ip_addr));
       add_new_service(mysql_global, ip_2_str(ip_addr), 22);
       --requests_outstanding;
       ++total_recorded;
       free(arg);
  } else { 
      // try to confirm the other direction
  //    printf("looking up name: %s \n", host->h_name);
      ares_gethostbyname(channel, host->h_name, 
                  AF_INET, name_2_ip_callback, arg);

  }
}

static void name_2_ip_callback(void *arg, int status, struct hostent *host){

  uint32_t ip_addr = *(uint32_t*)arg;

  if (status != ARES_SUCCESS || host == NULL) {
//      printf("UNKNOWN confirm failure for IP = %s \n", ip_2_str(ip_addr)); 
      goto end;
  }

  char *hostname = host->h_name;

  uint32_t answer = 0;
  char** p;
  char found = 0;
  for(p = host->h_addr_list; *p; p++) {
    answer = *(uint32_t*)*p;
    if(answer == ip_addr){ 
      found = 1;
      break;
    }
  }
  if(!found)
      hostname = ip_2_str(ip_addr); 

 // printf("adding new service: %s \n", hostname);
  add_new_service(mysql_global, hostname, 22);

  end:
    ++total_recorded;
    --requests_outstanding;
    free(arg);
}

#define MAX_OUTSTANDING 128

unsigned int notary_debug = DEBUG_ERROR;

int main(int argc, char** argv) {

  if(argc != 2){
    printf("usage: batch_dns <table_name> \n");
    exit(1);
  }

  if(dns_init()) 
    exit(1);

  mysql_global = open_mysql_conn("localhost", 
            "root", "moosaysthecow", "ssh");

  MYSQL *mysql_alt = open_mysql_conn("localhost", 
            "root", "moosaysthecow", "ssh");
		  
  char query_buf[128];
  snprintf(query_buf, 128, "SELECT ip_addr from %s order by RAND()", 
                argv[1]);

  if(mysql_real_query(mysql_alt, query_buf, strlen(query_buf)) != 0) {
      fprintf(stderr, "Error querying %s ip addresses to lookup: %s \n",
            argv[1], mysql_error(mysql_alt));
            return 1;
  }
  int total_requests = 0;

  MYSQL_RES *result = mysql_use_result(mysql_alt);
  if(!result) goto end;

  MYSQL_ROW row;
  requests_outstanding = 0; // global
  total_recorded = 0; // global

  my_bool all_requests_sent = 0;

  while(requests_outstanding > 0 || !all_requests_sent) {
  
      int simultaneous_dns_requests = 0;
      while(!all_requests_sent && 
          requests_outstanding < MAX_OUTSTANDING) {
         
         if((row = mysql_fetch_row(result)) == NULL) {
              all_requests_sent = 1;
              break;
         }

	 int *p_ip_addr = (int*) malloc(sizeof(int));
         *p_ip_addr = atoi(row[0]);

         ++requests_outstanding;
         ++total_requests;
            
       //  printf( "looking up IP: %s \n", ip_2_str(*p_ip_addr));
            ares_gethostbyaddr(channel, p_ip_addr, sizeof(uint32_t), 
                  AF_INET, ip_2_name_callback, p_ip_addr);

         ++simultaneous_dns_requests;

         if(total_requests % 500 == 0) {
          printf("outstanding = %d  sent = %d total = %d \n", 
              requests_outstanding, all_requests_sent, total_requests);
         }
         
         if(simultaneous_dns_requests > 5) break;

      } // end while

      // check DNS progress
      dns_batch_loop();


  } // end while

  end: 

  mysql_free_result(result);
  printf("Finished batch DNS Lookups.  Requested %d of total addresses. "
      " Inserted %d services (not all new). \n",total_requests, total_recorded);

  ares_destroy(channel);
  close_mysql_conn(mysql_alt);
  close_mysql_conn(mysql_global);
  return 0;
}
