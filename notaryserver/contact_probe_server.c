
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

/*
void check_cert_chain(ssl,host)
  SSL *ssl;
  char *host;
  {
    X509 *peer;
    char peer_CN[256];
    
    if(SSL_get_verify_result(ssl)!=X509_V_OK)
      berr_exit("Certificate doesn't verify");

    // Check the cert chain. The chain length
    //  is automatically checked by OpenSSL when we
    //  set the verify depth in the ctx

    // Check the common name
    peer=SSL_get_peer_certificate(ssl);
    X509_NAME_get_text_by_NID(X509_get_subject_name(peer),
      NID_commonName, peer_CN, 256);
    if(strcasecmp(peer_CN,host))
    err_exit("Common name doesn't match host name");
  }
*/

/*
int verify_callback (int ok, X509_STORE_CTX *store)
{
    char data[256];

    if (!ok)
    {
        X509 *cert = X509_STORE_CTX_get_current_cert(store);
        int  depth = X509_STORE_CTX_get_error_depth(store);
        int  err = X509_STORE_CTX_get_error(store);

        fprintf(stderr, "-Error with certificate at depth: %i\n", depth);
        X509_NAME_oneline(X509_get_issuer_name(cert), data, 256);
        fprintf(stderr, "  issuer   = %s\n", data);
        X509_NAME_oneline(X509_get_subject_name(cert), data, 256);
        fprintf(stderr, "  subject  = %s\n", data);
        fprintf(stderr, "  err %i:%s\n", err, X509_verify_cert_error_string(err) );
    }

    return ok;
}
*/

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
	printf("connecting to probe server %s : %d \n",
		inet_ntoa(host_addr.sin_addr), remote_port);
	if (connect(*client_sock, (struct sockaddr *)&host_addr, 
		sizeof(struct sockaddr)) == -1){
	    perror("connect");
	    exit(1);
	}
	printf("connected to probe server \n");

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
		printf("verify failed \n");
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


ssh_key_list* process_reply(notary_header* hdr, char* host_name, int total_len) {

	if(hdr->version != 1) {
		fprintf(stderr, "Invalid version #%d \n", hdr->version);
		return NULL;		
	}


	uint16_t name_len = ntohs(hdr->name_len);
	char *data = (char*) (hdr + 1);
/*	if(strcmp(data, host_name) != 0) {
		fprintf(stderr, "Host name in reply ('%s') does not match\n",
			data);
		return NULL;
	}
*/
	printf("name = %s with len = %d \n", data, name_len);
	ssh_key_info* key_info = (ssh_key_info*) (data + name_len);
	printf("keytype = %d \n", ntohs(key_info->key_type));
	uint32_t blob_size = (uint32_t) ntohs(key_info->key_len_bytes);

	printf("blob_size = %d \n", blob_size);
	if(blob_size + sizeof(notary_header) + sizeof(ssh_key_info) 
		> total_len) {
		fprintf(stderr, "Blob size is larger than packet can fit \n");
		return NULL;
	}

	char* blob = (char*) (key_info + 1);
	ssh_key_list* result = (ssh_key_list*)malloc(sizeof(ssh_key_list));
	result->key = key_from_blob(blob, blob_size);
	result->ip_addr = key_info->ip_addr;
	result->time_observed = key_info->time_observed;
	return result;
}

ssh_key_list* get_key_info_ssh(uint32_t pserver_ip,
        uint16_t pserver_port, char *host_name,
        uint16_t host_port, uint16_t key_type){

	// Send the message
	char buf[MAX_PACKET_LEN];

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
	printf("Wrote %d bytes on the SSL socket, waiting for response \n", 
		offset);

	offset = 0; 
	// loop until we have received replies (or time-out?) 
	while(1) {
		// Read Reply
		int num_read = SSL_read(ssl_connection, buf, MAX_PACKET_LEN);
		if (num_read == -1){
	    		perror("ssl recv");
	    		return;
		}
		printf("received %d bytes \n", num_read);
		offset += num_read;

		if(offset >= sizeof(notary_header)) {
			notary_header *hdr = (notary_header*) buf;
                    	uint16_t pkt_len = ntohs(hdr->total_len);
                    	if(pkt_len <= offset) {
                               	ssh_key_list* result = 
					process_reply(hdr,host_name,pkt_len);
				// test if this is the last record,
				// for now, it must be
				SSL_shutdown(ssl_connection);
				close(client_sock);
				return result;
			}
		}

	}
	
}

