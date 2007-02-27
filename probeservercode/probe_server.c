
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

#include "../common.h"
#include "probe_server.h"
#include "ssh-keyscan.h"

BIO *bio_err=0;

/* A simple error and exit routine*/
int err_exit(string)
  char *string;
  {
    fprintf(stderr,"%s\n",string);
    exit(0);
  }

/* Print SSL errors and exit*/
int berr_exit(string)
  char *string;
  {

    ERR_print_errors(bio_err);
    exit(-1);
  }


void destroy_ctx(ctx)
  SSL_CTX *ctx;
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


#define LISTEN_PORT 2221
#define KEYFILE "../keys/probe_server.key"
#define CERTFILE "../keys/probe_server.cert"
#define NUM_HOLDERS 1024

SSL_CTX *initialize_ctx(char *keyfile, char*cert_file) {
    SSL_METHOD *meth;
    SSL_CTX *ctx;
    
    /* Global system initialization*/
    SSL_library_init();
    OpenSSL_add_all_algorithms(); 
    SSL_load_error_strings();
      
    /* An error write context */
    bio_err=BIO_new_fp(stderr,BIO_NOCLOSE);
   
    /* Create our context*/
    meth=SSLv3_server_method();
    ctx=SSL_CTX_new(meth);

    /* Load our keys and certificates*/
    if(!(SSL_CTX_use_certificate_file(ctx,cert_file,SSL_FILETYPE_PEM)))
      berr_exit("Couldn't read certificate file");

    if(!(SSL_CTX_use_PrivateKey_file(ctx,keyfile,SSL_FILETYPE_PEM)))
      berr_exit("Couldn't read key file");

    if(!SSL_CTX_check_private_key(ctx)) 
      berr_exit("Private key check failed");

    printf("Successfully loaded private key and certificate\n");
    return ctx;
  }
      


// initializes SSL server socket and calls "accept"
// returns FD for the first client connection only
// (we assume that this is the notary server)
// "returns" ssl handle using pointer
SSL* init_ssl_serversock(char* ip, int* client_sock, int* server_sock) {
	struct sockaddr_in server_addr, client_addr;
	SSL_CTX *ctx;
	int addrlen = sizeof(struct sockaddr_in);
	SSL *ssl;

	// Build the SSL context
	ctx=initialize_ctx(KEYFILE, CERTFILE);

	if ((*server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	    perror("socket creation");
	    exit(-1);
	}

	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(LISTEN_PORT);
	if(!inet_aton(ip, (struct in_addr *)&(server_addr.sin_addr))) {
		perror("error with inet_aton\n");
		exit(-1);
	}

	if (bind(*server_sock, (struct sockaddr *) 
	   &server_addr,sizeof(server_addr)) < 0){ 
              	perror("ERROR on binding");
		exit(-1);
	}
 
	listen(*server_sock,5);
    
	BIO *sbio;
	printf("waiting for an incoming connection on %s : %d \n",
		inet_ntoa(server_addr.sin_addr), LISTEN_PORT);
        *client_sock = accept(*server_sock, 
              	(struct sockaddr *) &client_addr, &addrlen);
        if (*client_sock < 0) {
             	perror("ERROR on accept");
		exit(-1);
	}
	printf("Received connection from %s : %d \n", 
		inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));	

	
	sbio=BIO_new_socket(*client_sock, BIO_NOCLOSE);
	BIO_set_nbio(sbio, 1); // set sockets to non-blocking
	ssl=SSL_new(ctx);
	SSL_set_bio(ssl,sbio,sbio);
	
	if (SSL_accept(ssl)<=0){
	     	berr_exit("SSL Accept Error");
	}

	return ssl;
}


// returns 1 if this header was able to be processed by 
// the ssh-keyscan layer.  
int process_request(notary_header *hdr) {

	printf("processing request\n");
	char* data = (char*)(hdr + 1);
	printf("data: %s \n", data);

	int len = strlen(data);
	if(len > 1024) {
		printf("Ignoring request because domain name > 1024 bytes\n");
		return 1; 
	}
	char *host = (char*) malloc(len);
	if(host == NULL) {
		printf("Malloc out of memory \n");
		exit(1);
	}
	strcpy(host, data);
	printf("Handing %s to do_host \n", host);
	return do_host(host);
}


void process_socket_data(SSL* ssl, char *buf, int *offset) { 
	int hdr_len = sizeof(notary_header);

		int r = SSL_read(ssl, buf + *offset, 
			MAX_PACKET_LEN - *offset);
		printf("read %d bytes \n", r);
		int ret_val = SSL_get_error(ssl,r);
		if(ret_val == SSL_ERROR_ZERO_RETURN) {
			printf("Connection has been closed remotely\n");
			exit(-1);
		} else if(ret_val == SSL_ERROR_SYSCALL) {
			perror("Socket Syscall error");
			exit(-1);
		}else if(ret_val != SSL_ERROR_NONE) {
    			printf("SSL_read returned error. \n");
    			ERR_print_errors(bio_err);
			exit(-1);
		}

		printf("past ssl \n");	
		*offset += r;
		if(*offset >= hdr_len) {
			notary_header *hdr = (notary_header*) buf;
			int pkt_len = ntohs(hdr->name_len) + hdr_len;
			printf("hdr size = %d name size = %d \n", hdr_len,
				ntohs(hdr->name_len));
			if(pkt_len >= *offset) {
				// loop until the lower layer accepts
				// another connection
				while(!process_request(hdr)) {}
				// pkt_len bytes consumed
				memmove(buf, buf + pkt_len,
				 MAX_PACKET_LEN - pkt_len);
				*offset -= pkt_len;
			}else {
				printf("%d bytes has header but not full packet \n", *offset);
			}
		}else {
			printf("%d bytes is not enough for header \n", *offset);
		}
}



int main(int argc, char** argv) {

	// hardcode this for now, don't think its needed 
	// though	
	char *ip = "128.2.213.64";
	
	int client_sock, server_sock;
	ssh_key_holder ssh_keys[NUM_HOLDERS];
	fd_set readfds;
	struct timeval select_timeout;
	char buf[MAX_PACKET_LEN];
	int offset = 0;

	init_scankeys();

	SSL *ssl = init_ssl_serversock(ip, &client_sock, &server_sock);

	printf("Successful SSL setup.  Polling for requests.\n");


	// loop to keep reading requests sent by notary server,
	// dispatch them to be probed, and then reply to notary
	// server once probing is done.
	FD_ZERO(&readfds);	
	while(1) {
		// need to reset each time on linux
		select_timeout.tv_sec = 1;
		select_timeout.tv_usec = 0;
		FD_SET(client_sock , &readfds);
		
		int num_fds = select(client_sock + 1, &readfds, NULL, NULL,
					&select_timeout);
		if(num_fds > 0) {
			process_socket_data(ssl,buf, &offset);
		}else {
			printf("Select returned with nothing to read..\n");
		}

		int num_holders_used = conloop(ssh_keys, NUM_HOLDERS);
		if(num_holders_used > 0) {
			printf("***** main server loop got %d holders back! ****** \n",
			num_holders_used);
		}

	
  	} // end while

	SSL_free(ssl);
	close(client_sock);
	close(server_sock);
}



