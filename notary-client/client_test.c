
#include "common.h"
#include "notary_local.h" 
#include "file_list_convert.h"

SSHNotary *load_fake_replies_from_file(char *fname) { 

  SSHNotary *notary = init_ssh_notary(); 

  FILE *f = fopen(fname, "r"); 
  while(1) { 
    ssh_key_info_list *info_list = read_key_info_from_file(f);
    if(info_list == NULL) break; 

    // create fake server that 'observed' this data
    // and append it to the notary's list of servers 
    server_list *srv = (server_list*)malloc(sizeof(server_list)); 
    srv->received_reply = 1; 
    srv->notary_results = info_list;
    srv->ip_addr = 0; 
    srv->port = notary->num_servers; // just to give them a unique id
    srv->public_key = NULL; 
    __list_add(&srv->list, &(notary->notary_servers.list), 
                      (notary->notary_servers.list.next));
    ++(notary->num_servers); 
  }
  return notary; 
}
