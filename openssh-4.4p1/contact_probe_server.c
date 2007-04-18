
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h> 
#include <openssl/rand.h>
#include <openssl/x509.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/pem.h>

#include "contact_probe_server.h"
#include "key.h"
#include "../util/key_util.h"

BIO *bio_err=0;

/* A simple error and exit routine*/
int err_exit(char *string)
  {
    fprintf(stderr,"%s\n",string);
    exit(0);
  }

/* Print SSL errors and exit*/
int berr_exit(char* string)
  {

    ERR_print_errors(bio_err);
    exit(0);
  }


      
void destroy_ctx(SSL_CTX *ctx)
  {
    SSL_CTX_free(ctx);
  }



SSL_CTX *initialize_ctx(char *ca_file) {
    SSL_METHOD *meth;
    SSL_CTX *ctx;
	struct timeval t1,t2,t3;
    
	gettimeofday(&t1, NULL);

      /* Global system initialization*/
      SSL_library_init();
      OpenSSL_add_all_algorithms();
      SSL_load_error_strings();
      
      /* An error write context */
      bio_err=BIO_new_fp(stderr,BIO_NOCLOSE);

   
    /* Create our context*/
    meth=SSLv3_client_method();
    ctx=SSL_CTX_new(meth);

    /* Load the CAs we trust*/
    if(!(SSL_CTX_load_verify_locations(ctx,ca_file, NULL)))
      berr_exit("Couldn't read CA list");
    SSL_CTX_set_verify_depth(ctx,1);
	
	gettimeofday(&t2, NULL);
	int sec_diff = t2.tv_sec - t1.tv_sec; 
	DPRINTF(DEBUG_INFO,"first half (time > %d secs) \n", sec_diff);

    /* Load randomness */
// DW: this was causing long (e.g., 3 second) delays for 
// each SSL connection we set-up.  Apparently its just
// used to seed a RNG, so it should be able to be small
    if(!(RAND_load_file("/dev/urandom",256)))
      berr_exit("Couldn't load randomness");
	
	gettimeofday(&t3,NULL);
	sec_diff = t3.tv_sec - t2.tv_sec;
	DPRINTF(DEBUG_INFO, "second half ( time > %d secs) \n", sec_diff);

       
    return ctx;
  }

void getSSLClientConnection(server_list* server, char* cert_file) {
	SSL_CTX *ctx;
	BIO *sbio;
	struct sockaddr_in host_addr;

	server->ssl = NULL;        
	server->contact_succeeded = 0; // defaults to failure
        
	if ((server->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	    perror("socket");
	    return;
	}

	bzero(&host_addr, sizeof(struct sockaddr_in));
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(server->port);
	memcpy(&host_addr.sin_addr, &(server->ip_addr), sizeof(uint32_t));

	DPRINTF(DEBUG_INFO, "connecting to probe server %s : %d \n",
		inet_ntoa(host_addr.sin_addr), ntohs(host_addr.sin_port));
	if (connect(server->sock, (struct sockaddr *)&host_addr, 
		sizeof(struct sockaddr)) == -1){
	    printf("Failed to connect to probe server %s : %d :",
		inet_ntoa(host_addr.sin_addr), ntohs(host_addr.sin_port));
	    perror("");
	    printf("\n");
	    return;
	}
	DPRINTF(DEBUG_INFO, "connected to probe server \n");

	// TODO: we will set the socket as non-blocking

	// Connect over SSL
	ctx = initialize_ctx(cert_file);


	server->ssl = SSL_new(ctx);
	sbio = BIO_new_socket(server->sock, BIO_NOCLOSE);
	SSL_set_bio(server->ssl, sbio, sbio);

	if (SSL_connect(server->ssl)<=0){
	     server->ssl = NULL;
	     berr_exit("Error in the SSL connection");
	     return;
  	}


	DPRINTF(DEBUG_INFO, "server (0x%x) has SSL pointer (0x%x) \n",
		(uint32_t)server, (uint32_t)server->ssl);
	X509* peerCertificate;
	if(SSL_get_verify_result(server->ssl) == X509_V_OK){
		peerCertificate = SSL_get_peer_certificate(server->ssl);
	} else {
		DPRINTF(DEBUG_SSL, "probe server cert. "
		"failed verifications \n");
		ERR_print_errors(bio_err);
		server->ssl = NULL;
	}
}

void initiate_server_connections(server_list *all_servers, 
	char* cert_file) {

	server_list *server; 
        struct list_head *pos;
        DPRINTF(255, "Starting Initiate Server Loop \n");
        list_for_each(pos, &all_servers->list){
                server = list_entry(pos, server_list, list);
		getSSLClientConnection(server, cert_file);
	}
        DPRINTF(255, "Done with Initiate Server Loop \n");
}

// allocates and fills a packet buf.  caller must free the
// buffer when it is done
notary_header* pkt_create(char* name, uint16_t service_type,
	uint16_t service_port) {

	uint16_t name_len = strlen(name) + 1;
	uint16_t pkt_len = sizeof(notary_header) + name_len;
	notary_header* hdr = (notary_header*)malloc(pkt_len);
	bzero(hdr, pkt_len);
	hdr->version = 1;
	hdr->msg_type = TYPE_FETCH_REQ;
	hdr->total_len = htons(pkt_len);
	hdr->name_len = htons(name_len);
	hdr->service_type = htons(service_type);
	hdr->service_port = htons(service_port);
	char* data_start = (char*) (hdr + 1);
	memcpy(data_start, name, name_len);
	return hdr;	
}


void write_to_server(server_list *server, char* host_name, 
	uint16_t key_type, uint16_t service_port) {

	notary_header* hdr = pkt_create(host_name, 
				key_type, service_port);

	int msg_len = ntohs(hdr->name_len) + sizeof(notary_header);
	// TODO: switch this to non-blocking so we can time-out
	int offset = SSL_write(server->ssl, hdr, msg_len);
	if (offset == -1){
	    perror("ssl write");
	    return;
	}

	free(hdr);
	DPRINTF(DEBUG_SOCKET, "Wrote %d bytes on SSL socket to %s \n",
		offset, inet_ntoa(*(struct in_addr*)&server->ip_addr));

}

void send_server_requests(server_list *all_servers, char* host_name,
	uint16_t key_type, uint16_t service_port) {

	server_list *server;
        struct list_head *pos;
        DPRINTF(DEBUG_INFO, "Starting Server Request Loop \n");
        list_for_each(pos,&all_servers->list){
                server = list_entry(pos, server_list, list);
		if(server->ssl){ 
			write_to_server(server,host_name, 
				key_type, service_port);
		}
	}
        DPRINTF(DEBUG_INFO, "Done with Server Request Loop \n");
}

// takes a full packet and converts it into a ssh_result_list *
// element that can be stored by the client library.
void process_packet_data(server_list *server, char *hostname) {

	ssh_result_list *head = &(server->probe_results);
	notary_header* hdr = (notary_header*) server->data;
	uint16_t total_size = ntohs(hdr->total_len);

	if(hdr->version != 1) {
		DPRINTF(DEBUG_ERROR, "Invalid version #%d \n", 
			hdr->version);
		return;		
	}

	char *dns_name = (char*) (hdr +1);
	if(strncmp(hostname, dns_name, strlen(hostname)) != 0) {
		DPRINTF(DEBUG_ERROR, "Requsted hostname (%s) does "
			"not match  hostname in packet (%s)", 
			hostname, dns_name); 
		return;
	}
	int data_so_far = strlen(dns_name) + 1 + sizeof(notary_header);
	if(total_size == data_so_far){
		printf("no key in probe-server reply \n");
		return;
	}

	ssh_result_list* results = (ssh_result_list*)
				malloc(sizeof(ssh_result_list));

	ssh_key_info* key_info = (ssh_key_info*)HDR2DATA(hdr);
	int buf_size = ntohs(key_info->key_len_bytes);
	char* buf_start = (char*)(key_info + 1);	
	results->key = buf_to_key((uint8_t*)buf_start, buf_size,
			ntohs(hdr->service_type));

	int num_probes = ntohs(key_info->num_probes);
	int probes_len = sizeof(int) * num_probes;
	int* timestamps = (int*) malloc(probes_len);
	int* addresses = (int*) malloc(probes_len);
	int* probes_start = (int*) (buf_start + buf_size);
	int i;
	for(i = 0; i < num_probes; i++) {
		timestamps[i] = ntohl(probes_start[i]);
	}
	probes_start += num_probes;
	for(i = 0; i < num_probes; i++) {
		addresses[i] = probes_start[i];
	}
	
	results->timestamps = timestamps;
	results->addresses = addresses;
	results->num_probes = num_probes;
	list_add(&results->list, &head->list);

}


// once the main loop has read in the full notary-header, which tells
// us how long the whole message is, we use this to read the rest
// of the packet
void finish_reading_packet(server_list *server) {

	notary_header* hdr = (notary_header*)server->hdr_buf;
	uint16_t pkt_len = ntohs(hdr->total_len);
	DPRINTF(DEBUG_MESSAGE, "hdr says packet-len = %d \n", pkt_len);
	server->data  = (char*) malloc(pkt_len);
	memcpy(server->data, hdr, sizeof(notary_header));
	
	while(1) {
		// only read up to end of packet
		int num_read = SSL_read(server->ssl, 
				server->data + server->offset, 
				pkt_len - server->offset);
		if (num_read == -1){
	    		perror("ssl recv");
	    		return;
		}else if(num_read == 0) {
			DPRINTF(DEBUG_SOCKET, 
				"server closed socket connection \n");
			break;
		}
		DPRINTF(DEBUG_SOCKET, 
			"received %d bytes of message \n", num_read);
		server->offset += num_read;
        	if(pkt_len <= server->offset) {
			return;
		}
	}

}

// reads back replies form the server and processes them
// into ssh_result_list* entries
void read_from_server(server_list *server, char* hostname) {

	server->offset = 0; 
	// loop until we have received and process all replies 
	while(1) {
		// Read Reply
		DPRINTF(DEBUG_SOCKET, "waiting for header \n");
		int num_read = SSL_read(server->ssl, 
				server->hdr_buf + server->offset, 
				sizeof(notary_header) - server->offset);
		if (num_read == -1){
	    		perror("ssl recv");
	    		return;
		}else if(num_read == 0) {
			DPRINTF(DEBUG_SOCKET,
				"server closed socket connection \n");
			break;
		}
		DPRINTF(DEBUG_SOCKET, 
			"received %d bytes of header\n", num_read);
		server->offset += num_read;

		if(server->offset >= sizeof(notary_header)) {
			finish_reading_packet(server);
			// process data now, b/c a new reply
			// may come in and overwrite data
			process_packet_data(server, hostname);
			free(server->data);
		}
		server->offset = 0;
	}
	SSL_shutdown(server->ssl);
	close(server->sock);
	
}

void read_server_replies(server_list *all_servers, char* host_name) {

	server_list* server;
        struct list_head *pos;
        DPRINTF(255, "Starting Server Reply Loop \n");
        list_for_each(pos,&(all_servers->list)){
                server = list_entry(pos, server_list, list);
		if(server->ssl) 
			read_from_server(server, host_name);
	}
        DPRINTF(255, "Done with Server Reply Loop \n");
}


void contact_probe_servers(server_list* servers, char* host_name,
	uint16_t key_type, uint16_t service_port, char* cert_file) {

	initiate_server_connections(servers, cert_file);
	
	send_server_requests(servers, host_name, key_type, service_port);

	read_server_replies(servers, host_name);
}



/*
	uint16_t total_len = ntohs(hdr->total_len);
                char* data = (char*)hdr;
                for(int i = 0; i < total_len; i = i + 4) {
                        printf("%d %d %d %d \n", data[i],
                                data[i+1], data[i+2], data[i+3]);
                }		
*/
