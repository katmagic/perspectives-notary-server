#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "common.h"
#include "debug.h"
#include "notary_crypto.h"
#include "notary_util.h"
#include "net_util.h"
#include "notary_local.h"
#include "str_buffer.h" 

ssh_key_info_list* parse_message(char *buf, int msg_len) {
  notary_header *hdr = (notary_header*)buf;
  int hdr_len = HEADER_SIZE(hdr);
  char *serviceid = (char*) (hdr + 1);
  DPRINTF(DEBUG_INFO, "Reply for serviceid = '%s' \n", serviceid);
  char *data = ((char*)buf) + hdr_len;
  int total_len = ntohs(hdr->total_len);
  if(total_len != msg_len) {
    DPRINTF(DEBUG_ERROR, "Length mismatch header = %d actual = %d \n",
        total_len, msg_len);
    return NULL;
  }
  if(hdr->msg_type == TYPE_FETCH_REPLY_EMPTY) {
    DPRINTF(DEBUG_INFO, "Server found no service-record \n"); 
    return NULL; 
  }
  int data_len = total_len - hdr_len;
  return list_from_data(data, data_len, SIGNATURE_LEN);
}



// caller should free memory
notary_header* create_request(char*hostname, uint16_t service_type) {
  int name_len = strlen(hostname) + 1;
  int total_len = sizeof(notary_header) + name_len;
  notary_header* hdr = (notary_header*)malloc(total_len);
  hdr->version = 1;
  hdr->msg_type = TYPE_FETCH_REQ;
  hdr->total_len = htons(total_len);
  hdr->name_len = htons(name_len);
  hdr->service_type = htons(service_type);
  char* name_start = (char*)(hdr+1);
  memcpy(name_start, hostname, name_len);
  make_lowercase(name_start, name_len - 1); // notary only deals with lower-case
  return hdr;
}

void add_notary_server(SSHNotary *notary, uint32_t ip_address, uint16_t port, 
    char* key){
  server_list *tmp = (server_list*)malloc(sizeof(server_list));
  tmp->ip_addr = ip_address;
  tmp->notary_results = NULL; // this is set after data is received + parsed 
  tmp->port = port;
  tmp->public_key = key;
  tmp->received_reply = 0;
  tmp->consistent_secs = 0;
  __list_add(&tmp->list,&(notary->notary_servers.list),
      (notary->notary_servers.list.next));
  DPRINTF(DEBUG_INFO, "Adding notary server: %s : %d \n",
      inet_ntoa(*(struct in_addr*)&ip_address), tmp->port);
  ++(notary->num_servers);
}

SSHNotary* init_ssh_notary(){

  SSHNotary *n = (SSHNotary*)malloc(sizeof(SSHNotary));
  n->num_servers = 0;
  INIT_LIST_HEAD(&n->notary_servers.list);
  return n;
}

// for each server, loop through its probe_info list
// and free all content.
// this function should be called when the notary is free,
// or when a new host is being checked
void free_key_info(SSHNotary* notary) {
  DPRINTF(DEBUG_INFO, "Freeing key_info data for all servers\n");
  server_list *server;
  struct list_head *pos;
  list_for_each(pos,&notary->notary_servers.list){
    server = list_entry(pos, server_list, list);

    free_key_info_list(server->notary_results); 
  }
}

void free_ssh_notary(SSHNotary* notary){

  free_key_info(notary); // call before freeing server info

  server_list *server;
  struct list_head *pos, *q;
  list_for_each_safe(pos, q, &notary->notary_servers.list){
    server = list_entry(pos, server_list, list);
    // Firefox, free base64 key
    if(server->public_key) { 
      //  RSA_free(server->public_key);
      free(server->public_key); 
    } 
    list_del(&server->list);
    free(server);
  }
  free(notary);
}

// expects the port in host byte order, the ip address in network byte order
// (i.e., as stored in the server struct) 
server_list * find_server(SSHNotary* notary, uint32_t server_ip, uint16_t server_port){

  server_list *server;
  struct list_head *pos, *q;
  list_for_each_safe(pos, q, &notary->notary_servers.list){
    server = list_entry(pos, server_list, list);
    if(server->ip_addr == server_ip && 
        server->port == server_port)
      return server;
  }
  return NULL;
}


// print all information received from probe servers
void print_notary_reply(FILE * f, SSHNotary *notary) {
  server_list *server;
  struct list_head *outer_pos;
  list_for_each(outer_pos,&notary->notary_servers.list){
    server = list_entry(outer_pos, server_list, list);

    printf("***********  Probes from server %s:%d ********** \n", 
        ip_2_str(server->ip_addr), server->port);

    print_key_info_list(f, server->notary_results);
  }
}

//Get Notary Reply 
char *get_notary_reply(SSHNotary *notary) {
  server_list *server;
  struct list_head *outer_pos;
  int response_len = 0;
  int max_len = 4096;
  int n = 0;
  // Macro 4096 
  char *response = (char *) malloc(sizeof(char) * max_len);
  if(!response)
  {
    return NULL;
  }
  list_for_each(outer_pos,&notary->notary_servers.list){
    server = list_entry(outer_pos, server_list, list);

    if(response_len >= max_len) { 
      printf("bailing from get_notary_reply \n"); 
      return response; 
    } 
    n = snprintf(response + response_len, max_len - response_len,
        "***********  Probes from server %s:%d ********** \n", 
        ip_2_str(server->ip_addr), server->port);

    response_len += n;

    get_key_info_list(response, &response_len, max_len, 
        server->notary_results);
  }
  return response;
}


int get_number_of_notaries(SSHNotary *notary)
{
  return notary->num_servers;
}



/*  
 *
 *  this function needs to be rewritten now that we do not use full
 *  ssh keys on the client (instead we use 16-byte hashes)

// a new print function that collects all information about a particular
// key together.  It should be much more readable.  
void print_probe_info2(SSHNotary *notary) {
Key* all_keys[MAX_NUM_KEYS];
int key_count = 0;

// loop through each reply list to find all unique keys
server_list *server;
struct list_head *outer_pos, *inner_pos;
list_for_each(outer_pos,&notary->notary_servers.list){
server = list_entry(outer_pos, server_list, list);
ssh_key_info_list *list_elem;
list_for_each(inner_pos,&(server->notary_results.list)) {
list_elem = list_entry(inner_pos, 	
ssh_key_info_list, list);

BOOL key_found = FALSE;
int i;
Key *k = info_to_ssh_key(list_elem->info);
// test if we've already seen this key
for(i = 0; i < key_count; i++) {
if(key_equal(all_keys[i], k)){
key_found = TRUE;
break;
}
}
if(!key_found && key_count < MAX_NUM_KEYS) {
// if not, add it to the list
all_keys[key_count] = k;
key_count++;
}else {
free(k);
}
}
}

// loop through each key, printing all observations for that key
int j;
for(j = 0; j < key_count; j++) {

printf("\n***************** [ Key #%d of %d ] ********************* \n\n",
(j+1), key_count);	
key_write(all_keys[j], stdout);
fputs("\n\n", stdout);

server_list *server;
struct list_head *outer_pos, *inner_pos;
list_for_each(outer_pos,&notary->notary_servers.list){
server = list_entry(outer_pos, server_list, list);

printf("Observed Key-timespans from Notary Server = %s :\n", 
ip_2_str(server->ip_addr));
ssh_key_info_list *list_elem;
list_for_each(inner_pos, &server->notary_results.list) {
list_elem = list_entry(inner_pos, ssh_key_info_list, list);
Key *k = info_to_ssh_key(list_elem->info);
if(key_equal(all_keys[j], k)) {
print_key_info_timespans(list_elem->info);
}
}
}
}


}
*/

// similar to fgets, but for a buffer instead of a file 
char * get_line(char *input_buf, char *output_buf, int buf_size) {
  char *end = input_buf; 
  BOOL is_done = FALSE;           
  char *limit = input_buf + buf_size - 2; // need space for \0

  while(*end != '\n' && end != limit) {
    if(*(end++) == EOF){
      is_done = TRUE;        
      break;
    }
  }
  int len = (end - input_buf) + 1;
  memcpy(output_buf, input_buf, len);
  output_buf[len] = 0; // null terminate at one past

  return is_done ? NULL : (end + 1); 
}

#define PEM_PUB_START "-----BEGIN PUBLIC KEY-----\n"
#define PEM_PUB_END "-----END PUBLIC KEY-----\n"

char *read_single_pubkey(char *input_buf, char *output_buf, int max_len, int *bytes_read) {

  int offset = 0;
  char line[1024];
  BOOL key_started = FALSE; 

  char *ptr = input_buf; 
  while( (ptr = get_line(ptr, line, 1024)) != NULL) {
    int line_len; 
    if(strcmp(PEM_PUB_START, line) == 0){
      key_started = TRUE;
      continue;
    }
    if(!key_started) 
      continue;

    line_len = strlen(line);
    if(offset + line_len > max_len){
      DPRINTF(DEBUG_ERROR, "error, pubkey file larger than buf \n");
      exit(1);
    }

    if(strcmp(PEM_PUB_END, line) == 0) {
      *bytes_read = offset; 
      output_buf[offset] = 0x0; 
      return ptr;
    }

    // don't copy null terminator
    memcpy(output_buf + offset, line, line_len);
    offset += line_len;


  }
  DPRINTF(DEBUG_ERROR, "Error: reached EOF before finished reading key \n");
  exit(1);
  return NULL; // shutup compiler
}


#define MAX_FILE_SIZE 100000 
#define MAX_LINE_LENGTH 1024

void load_notary_server_file(SSHNotary *notary, char *fname) {
  char buf[MAX_FILE_SIZE];
  assert(fname);

  FILE *f = fopen(fname, "r");
  if(f == NULL) {
    DPRINTF(DEBUG_ERROR, 
        "Notary Error: Invalid notar-list file %s \n", fname);
    return;
  }

  size_t bytes_read = fread(buf, 1, MAX_FILE_SIZE, f);
  if(ferror(f)) {
    DPRINTF(DEBUG_ERROR, "Error reading client config file: %s \n", fname);
    return;
  }

  load_notary_servers(notary, buf, bytes_read);

}

void load_notary_servers(SSHNotary *notary, char* data, int buf_len){

  char buf[MAX_LINE_LENGTH];

  char *ptr = data;
  char *end = data + buf_len - 1; 
  while((ptr = get_line(ptr, buf, MAX_LINE_LENGTH)) != NULL 
      && ptr < end) {

    if(*buf == '\n') continue;
    if(*buf == '#') continue;
    int size = strlen(buf);
    buf[size - 1] = 0x0; // replace '\n' with NULL
    char *delim = strchr(buf,' ');
    if(delim == NULL) {
      DPRINTF(DEBUG_ERROR, 
          "Ignoring malformed line: %s \n", buf);
      continue;
    }
    *delim = 0x0;

    uint32_t ip_addr = str_2_ip(buf);
    int port = (uint16_t) atoi(delim + 1);
    char buf2[1024];
    int key_len = -1; 
    ptr = read_single_pubkey(ptr, buf2, 1024, &key_len);
    // RSA * pub_key = key_from_buf(buf2, key_len, FALSE);
    DPRINTF(DEBUG_INFO, "loaded key for server '%s' : %d \n", 
        ip_2_str(ip_addr), port);
    // TODO: strdup base64 key
    add_notary_server(notary, ip_addr, port, strdup(buf2));
  }
}

void parse_client_config(client_config *conf, char *fname){ 
  char buf[1024];
  FILE *f;
  assert(fname);

  f = fopen(fname, "r");
  if(f == NULL) {
    DPRINTF(DEBUG_ERROR,
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
    if(strcmp(buf,"debug") == 0) { 
      conf->debug = atoi(value);
    } else if(strcmp(buf, "timeout_secs") == 0) {
      conf->timeout_secs = atof(value);
    } else if(strcmp(buf, "num_notaries") == 0){
      conf->num_notaries = atoi(value);
    } else if(strcmp(buf, "quorum") == 0) {
      conf->quorum = atof(value);
    } else if(strcmp(buf, "quorum_duration_days") == 0) {
      conf->quorum_duration_days = atof(value);
    } else if(strcmp(buf, "max_stale_days") == 0) {
      conf->max_stale_days = atof(value);
    } else {
      DPRINTF(DEBUG_ERROR, "Unknown config value %s : %s \n",
          buf, value);
    }
  }		
}


// below is ugly code to generate SVG images representing the key timespans

typedef struct key_color_pair_t { 
  char key_data[KEY_LEN]; 
  char *color;
} key_color_pair; 

#define MAX_COLORS 8
char* colors[MAX_COLORS] = { "blue","purple", "yellow", "orange","cyan", "green", "red","brown" };  

// returns num_keys
int setup_color_info(key_color_pair *color_info, Notary *notary, uint32_t cutoff) { 
  struct list_head *outer_pos, *inner_pos;
  int num_keys = 0; 
  char *key_buf = NULL; 
  int *timespans;

  while(1) { 
    // we try to find the most recently seen key that has not yet been assigned a color
    uint32_t most_recent_unmatched_end = 0; 
    char* most_recent_unmatched_key = NULL; 
    list_for_each(outer_pos,&notary->notary_servers.list){
      server_list *server = list_entry(outer_pos, server_list, list);
      if(server->notary_results == NULL)
        continue;
      list_for_each(inner_pos,&server->notary_results->list) {
        ssh_key_info_list *list_elem = list_entry(inner_pos, ssh_key_info_list, list);
        int i; 
        BOOL key_found; 
        uint32_t most_recent = 0; // most recent obs. for this key  
        ssh_key_info *info = list_elem->info; 
        int len = ntohs(info->key_len_bytes);
        int num_spans = ntohs(info->num_timespans);
        key_buf = (char*)(list_elem->info + 1);
        timespans = (int*)(key_buf + len);
        for(i = 0; i < num_spans; i++){
          uint32_t t_end = ntohl(timespans[1]);
          if(t_end > most_recent)  
            most_recent = t_end; 
          timespans += 2;
        } 
        if(most_recent < cutoff)  
          continue; 

        key_found = FALSE;
        for(i = 0; i < num_keys; i++) { 
          if(!memcmp(key_buf,color_info[i].key_data,KEY_LEN)){
            key_found = TRUE;
            break; 
          }
        }
        if(!key_found && num_keys < MAX_COLORS) {
          if(most_recent > most_recent_unmatched_end) { 
            most_recent_unmatched_end = most_recent; 
            most_recent_unmatched_key = key_buf;  
          }
        } 
      }
    } 
    if(most_recent_unmatched_key) { 
      memcpy(color_info[num_keys].key_data,most_recent_unmatched_key,KEY_LEN);
      color_info[num_keys].color = colors[num_keys]; 
      num_keys++;
    }else { 
      break; // all keys have been assigned, or all colors used
      // keys not assigned a color will appear as grey
    } 
  } // end while   
  return num_keys; 
} 


char* get_reply_as_svg(const char* service_id, SSHNotary *notary, uint32_t len_days) {
  int i; 
  struct timeval now; 
  uint32_t cur_secs, cutoff; 
  server_list *server;
  struct list_head *outer_pos, *inner_pos;
  int height, width = 700; 
  int x_offset = 160;
  int y_offset = 40;  
  float pixels_per_day = (width - x_offset - 20) / len_days;  
  int rec_height = 10;  
  int num_keys = 0;
  int y_cord = y_offset; 
  key_color_pair *color_info = (key_color_pair*)
    malloc(MAX_COLORS * sizeof(key_color_pair)); 
  char buf[1024]; 
  str_buffer *b = str_buffer_new(1024);   
  ssh_key_info *info; 
  char *key_buf;
  BOOL grey_used = FALSE; 

  gettimeofday(&now, NULL); 
  cur_secs = now.tv_sec; 
  cutoff = cur_secs - DAY2SEC(len_days);  

  num_keys = setup_color_info(color_info, notary, cutoff);  
  height = num_keys * 30 + get_number_of_notaries(notary) * 20 + y_offset + 30; 

  str_buffer_append(b,"<?xml version=\"1.0\"?>\n" 
      "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" "
      "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"); 
  snprintf(buf,1024,"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\""
      " width=\"%d\" height=\"%d\">",width,height); 
  str_buffer_append(b,buf); 
  snprintf(buf,1024,"<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"white\" />",
      width,height);  
  str_buffer_append(b,buf); 
  //	snprintf(buf,1024,"<text x=\"80\" y=\"%d\" font-size=\"15\">Key History for %s</text>\n", 
  //								18,service_id);
  //	str_buffer_append(b,buf); 
  //	y_cord += 20;  

  snprintf(buf,1024,"<text x=\"%d\" y=\"%d\" font-size=\"15\" >"
      "Key History (Days) </text>\n",
      x_offset + 70, y_cord); 
  str_buffer_append(b,buf); 
  snprintf(buf,1024,"<text x=\"%d\" y=\"%d\" font-size=\"15\">Notary and Current Key</text>\n",
      4, y_cord); 
  str_buffer_append(b,buf); 
  y_cord += 20; 

  // loop through each reply list to draw each valid timespan 
  list_for_each(outer_pos,&notary->notary_servers.list){
    char *most_recent_color = "white"; // none 
    uint32_t most_recent_end = 0; 
    ssh_key_info_list *list_elem;
    server = list_entry(outer_pos, server_list, list);
    y_cord += 20;
    snprintf(buf,1024,"<text x=\"%d\" y=\"%d\" font-size=\"12\">%s</text>\n", 
        4,y_cord + 7,ip_2_str(server->ip_addr));
    str_buffer_append(b,buf); 	

    if(server->notary_results == NULL)
      continue; 

    list_for_each(inner_pos,&server->notary_results->list) {
      char *color = "grey"; // default color 
      list_elem = list_entry(inner_pos, ssh_key_info_list, list);
      info = list_elem->info; 

      key_buf = (char*)(list_elem->info + 1);
      for(i = 0; i < num_keys; i++) { 
        if(!memcmp(key_buf,color_info[i].key_data,KEY_LEN)){
          color = color_info[i].color;
          break; 
        }
      } 

      int len = ntohs(info->key_len_bytes);
      int *timespans = (int*)(key_buf + len);
      int num_spans = ntohs(info->num_timespans);
      for(i = 0; i < num_spans; i++){
        uint32_t t_start = ntohl(timespans[0]);
        uint32_t t_end = ntohl(timespans[1]);
        if(t_end < cutoff) { 
          timespans += 2;
          continue; 
        } 
        if(t_start < cutoff) 
          t_start = cutoff; 
        if(t_end > most_recent_end) { 
          most_recent_end = t_end;
          most_recent_color = color;
        }  		 

        if(!strcmp(color,"grey")) {  
          grey_used = TRUE; 
        } 
        int time_since = cur_secs - t_end;
        int duration = t_end - t_start; 
        int x_cord = x_offset + (int)(pixels_per_day * SEC2DAY(time_since)); 
        float width =  (pixels_per_day * SEC2DAY(duration));

        // a timespan with no width is not shown	
        if(width > 0) {  
          snprintf(buf,1024,"<rect x=\"%d\" y=\"%d\" "
              "width=\"%f\" height=\"%d\" fill=\"%s\" "
              "rx=\"1\" stroke=\"black\" stroke-width=\"1px\" />\n",
              x_cord,y_cord,width,rec_height,color);	
          str_buffer_append(b,buf); 
        } 
        timespans += 2;
      }
      // print "current key" circle 
      snprintf(buf,1024,"<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" "
          "fill=\"%s\" rx=\"5\" stroke=\"black\" stroke-width=\"1px\" />\n",
          x_offset - 30, y_cord,most_recent_color);	
      str_buffer_append(b,buf); 

    }
  }

  // draw Days axis 
  for(i = 0; i < 11; i++) { 
    float days = i * (len_days / 10.0); 
    int x = x_offset + (pixels_per_day * days);
    int y = y_offset + 30; 
    if(len_days < 10 && days != 0)  {  // print with decimal
      snprintf(buf,1024,"<text x=\"%d\" y=\"%d\" font-size=\"15\">%.1f</text>\n",
          x,y,days);
    } else { 
      snprintf(buf,1024,"<text x=\"%d\" y=\"%d\" font-size=\"15\">%.0f</text>\n",
          x,y,days);
    } 
    str_buffer_append(b,buf); 
    snprintf(buf,1024,"<path d = \"M %d %d L %d %d\" stroke = \"grey\" "
        "stroke-width = \"1\"/>",x, y,x, y_cord + 20); 
    str_buffer_append(b,buf); 	
  } 

  // draw legend mapping colors to keys 
  y_cord += 30;
  for(i = 0; i < num_keys && i <= MAX_COLORS; i++) { 
    snprintf(buf,1024,"<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" "
        "fill=\"%s\" rx=\"0\" stroke=\"black\" stroke-width=\"1px\" />\n",
        x_offset, y_cord,color_info[i].color);	
    str_buffer_append(b,buf); 
    char *key_str = buf_2_hexstr(color_info[i].key_data,KEY_LEN);
    snprintf(buf,1024,"<text x=\"%d\" y=\"%d\" font-size=\"15\">%s</text>\n", 
        x_offset + 15,y_cord + 9, key_str); 
    str_buffer_append(b,buf); 
    y_cord += 20; 
  } 

  // extra legend entry for default color, if needed
  if (grey_used) { 
    snprintf(buf,1024,"<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" "
        "fill=\"%s\" rx=\"5\" stroke=\"black\" stroke-width=\"1px\" />\n",
        x_offset, y_cord,"grey");	
    str_buffer_append(b,buf); 
    snprintf(buf,1024,"<text x=\"%d\" y=\"%d\" font-size=\"15\">%s</text>\n", 
        x_offset + 15, y_cord + 9, "all other keys"); 
    str_buffer_append(b,buf); 
  } 
  str_buffer_append(b,"</svg>\n"); 
  char *str = str_buffer_get(b); 
  str_buffer_free(b); 
  return str; 
}

char* get_reply_as_xml(SSHNotary *notary) {
  server_list *server;
  struct list_head *outer_pos, *inner_pos;
  str_buffer *b = str_buffer_new(1024);   
  ssh_key_info *info; 
  ssh_key_info_list *list_elem;
  char buf[1024];

  str_buffer_append(b, "<response>\n");
  // loop through each reply list to draw each valid timespan 
  list_for_each(outer_pos,&notary->notary_servers.list){
    str_buffer_append(b, "<server>\n");
    server = list_entry(outer_pos, server_list, list);

    str_buffer_append(b, "\t<ip>");
    str_buffer_append(b, ip_2_str(server->ip_addr)); 
    str_buffer_append(b, "</ip>\n");

    if(server->notary_results == NULL) { 
      str_buffer_append(b, "</server>\n");
      continue; 
    }

    list_for_each(inner_pos, &server->notary_results->list) {
      list_elem = list_entry(inner_pos, ssh_key_info_list, list);
      info = list_elem->info; 
      xml_from_key_info(buf, sizeof(buf), info);
    }
    str_buffer_append(b, buf);
    str_buffer_append(b, "</server>\n");
  }

  str_buffer_append(b, "</response>\n");
  char *str = str_buffer_get(b); 
  str_buffer_free(b); 
  return str; 
}

//notary-http needs this so I moved it out of get_reply_as_xml
void xml_from_key_info(char *buf, int bufsize, ssh_key_info *info){
  int i, tmp;
  char *key_buf;

  int len        = ntohs(info->key_len_bytes);
  key_buf        = (char*)(info + 1); //wha??
  char *key_str  = buf_2_hexstr(key_buf,KEY_LEN);
  int *timespans = (int*)(key_buf + len);
  int num_spans  = ntohs(info->num_timespans);

  tmp = snprintf(buf, bufsize, "\t<result>\n\t\t<key>%s</key>\n", key_str);
  buf     += tmp;
  bufsize -= tmp;

  for(i = 0; i < num_spans; i++){
    uint32_t t_start = ntohl(timespans[0]);
    uint32_t t_end   = ntohl(timespans[1]);
    tmp = snprintf(buf, bufsize, 
        "\t\t<timestamp>\n"
        "\t\t\t<start> %d </start>\n"
        "\t\t\t<end>   %d </end>\n"
        "\t\t</timestamp>\n",
        t_start, t_end);
    buf       += tmp;
    bufsize   -= tmp;
    timespans += 2;
  }

  snprintf(buf, bufsize, "\t</result>\n");
}

char* get_reply_as_json(SSHNotary *notary) {
  int i; 
  server_list *server;
  struct list_head *outer_pos, *inner_pos;
  char buf[1024]; 
  str_buffer *b = str_buffer_new(1024);   
  ssh_key_info *info; 
  char *key_buf, first_server = 1;

  // loop through each reply list to draw each valid timespan 
  list_for_each(outer_pos,&notary->notary_servers.list){
    char first_obj = 1; 
    ssh_key_info_list *list_elem;
    server = list_entry(outer_pos, server_list, list);
    if(first_server) { 
      str_buffer_append(b,"[ { "); 
      first_server = 0; 
    }
    else 
      str_buffer_append(b,", { "); 
    str_buffer_append(b,"\"server\" : \""); 
    str_buffer_append(b,ip_2_str(server->ip_addr)); 
    str_buffer_append(b,"\"\n , \"obs\" : ["); 

    if(server->notary_results == NULL) { 
      str_buffer_append(b," ] }\n"); 
      continue; 
    }

    list_for_each(inner_pos,&server->notary_results->list) {
      list_elem = list_entry(inner_pos, ssh_key_info_list, list);
      info = list_elem->info; 
      if(first_obj) 
        first_obj = 0; 
      else
        str_buffer_append(b," , "); 
      key_buf = (char*)(list_elem->info + 1); //wha??
      char *key_str = buf_2_hexstr(key_buf,KEY_LEN);
      str_buffer_append(b,"{ \"key\" : \""); 
      str_buffer_append(b,key_str); 
      str_buffer_append(b,"\",\n \"timestamps\" : ["); 
      int len = ntohs(info->key_len_bytes);
      int *timespans = (int*)(key_buf + len);
      int num_spans = ntohs(info->num_timespans);
      for(i = 0; i < num_spans; i++){
        if(i != 0) 
          str_buffer_append(b,", "); 
        uint32_t t_start = ntohl(timespans[0]);
        uint32_t t_end = ntohl(timespans[1]);
        snprintf(buf, 1024, "{ \"start\" : %d , \"end\" : %d }",t_start, t_end);
        str_buffer_append(b,buf); 
        timespans += 2;
      }
      str_buffer_append(b,"] }\n"); // end timespans list and obs object
    }
    str_buffer_append(b,"] }\n"); // end observation list and server object
  }
  str_buffer_append(b,"]\n"); // end response list
  char *str = str_buffer_get(b); 
  str_buffer_free(b); 
  return str; 
}
