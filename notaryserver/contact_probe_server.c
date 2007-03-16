
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


#define SELF_SIGNED_CERT "../keys/probe_server.cert"

SSL_CTX *initialize_ctx(char *ca_file) {
    SSL_METHOD *meth;
    SSL_CTX *ctx;
    
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

    /* Load randomness */
    if(!(RAND_load_file("/dev/urandom",1024*1024)))
    berr_exit("Couldn't load randomness");
       
    return ctx;
  }

SSL * getSSLClientConnection(uint32_t remote_ip, uint16_t remote_port,
			int *client_sock) {
	SSL_CTX *ctx;
	SSL *ssl;
	BIO *sbio;
	struct sockaddr_in host_addr;

	// Build the SSL context
	ctx=initialize_ctx(SELF_SIGNED_CERT);

	if ((*client_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	    perror("socket");
	    return NULL;
	}

	bzero(&host_addr, sizeof(struct sockaddr_in));
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(remote_port);
	memcpy(&host_addr.sin_addr, &remote_ip, sizeof(uint32_t));
	DPRINTF(DEBUG_INFO, "connecting to probe server %s : %d \n",
		inet_ntoa(host_addr.sin_addr), remote_port);
	if (connect(*client_sock, (struct sockaddr *)&host_addr, 
		sizeof(struct sockaddr)) == -1){
	    perror("connect");
	    exit(1);
	}
	DPRINTF(DEBUG_INFO, "connected to probe server \n");

	// Connect the SSL socket
	ssl=SSL_new(ctx);
	sbio=BIO_new_socket(*client_sock, BIO_NOCLOSE);
	SSL_set_bio(ssl,sbio,sbio);
	if (SSL_connect(ssl)<=0){
	     berr_exit("Error in the SSL connection");
	     return NULL;
  	}

	X509* peerCertificate;

	if(SSL_get_verify_result(ssl) == X509_V_OK){
		peerCertificate = SSL_get_peer_certificate(ssl);
	} else {
		DPRINTF(DEBUG_SSL, "probe server cert. failed verifications \n");
		ERR_print_errors(bio_err);
	}

	return ssl;
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


// once the main loop has read in the full notary-header, which tells
// us how long the whole message is, we 
void process_single_message(ssh_msg_list *head, 
		notary_header* hdr,
		SSL* ssl_connection,char *host_name) {

	uint16_t pkt_len = ntohs(hdr->total_len);
	DPRINTF(DEBUG_MESSAGE, "hdr says packet-len = %d \n", pkt_len);
	char *buf = (char*) malloc(pkt_len);
	memcpy(buf, hdr, sizeof(notary_header));
	int offset = sizeof(notary_header);
	while(1) {
		int num_read = SSL_read(ssl_connection, buf + offset, 
				pkt_len - offset);
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
		offset += num_read;
        	if(pkt_len <= offset) {
			if(hdr->version != 1) {
				DPRINTF(DEBUG_ERROR, 
				"Invalid version #%d \n", 
				hdr->version);
				return;		
			}		

			ssh_msg_list* tmp = (ssh_msg_list*)
				malloc(sizeof(ssh_msg_list));
			tmp->hdr = (notary_header*)buf;
	
			list_add(&tmp->list, &head->list);
			break;
		}
	}

}

ssh_key_info* get_key_info_ssh(ssh_msg_list *head , uint32_t pserver_ip,
        uint16_t pserver_port, char *host_name,
        uint16_t host_port, uint16_t key_type){

	char small_buf[sizeof(notary_header)];

	int client_sock; 
	SSL* ssl_connection = getSSLClientConnection(pserver_ip, 
			pserver_port, &client_sock);
	notary_header* hdr = pkt_create(host_name, key_type, host_port);

	int msg_len = ntohs(hdr->name_len) + sizeof(notary_header);
	int offset = SSL_write(ssl_connection, hdr, msg_len);
	if (offset == -1){
	    perror("ssl write");
	    return;
	}

	free(hdr);
	DPRINTF(DEBUG_SOCKET, 
		"Wrote %d bytes on the SSL socket, waiting for response \n", 
		offset);

	offset = 0; 
	// loop until we have received replies (or time-out?) 
	while(1) {
		// Read Reply
		DPRINTF(DEBUG_SOCKET, "waiting for header \n");
		int num_read = SSL_read(ssl_connection, small_buf + offset, 
				sizeof(notary_header) - offset);
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
		offset += num_read;

		if(offset >= sizeof(notary_header)) {
			notary_header *hdr = (notary_header*) small_buf;
			process_single_message(head, hdr, 
					ssl_connection,host_name);
		}

	}
	SSL_shutdown(ssl_connection);
	close(client_sock);
	
}

