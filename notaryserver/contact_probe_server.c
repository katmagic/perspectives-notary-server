
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

    printf("loading public key??\n");

    /* Load randomness */
    if(!(RAND_load_file("/dev/urandom",1024*1024)))
    berr_exit("Couldn't load randomness");
       
    return ctx;
  }

SSL * getSSLConnection(char *remote_ip, uint16_t remote_port) {
	SSL_CTX *ctx;
	SSL *ssl;
	BIO *sbio;
	int sockfd;
	struct sockaddr_in host_addr;

	// Build the SSL context
	ctx=initialize_ctx(SELF_SIGNED_CERT);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	    perror("socket");
	    return NULL;
	}

	bzero(&host_addr, sizeof(struct sockaddr_in));
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(remote_port);
	inet_aton(remote_ip, (struct in_addr *)&host_addr.sin_addr.s_addr);

	printf("connecting to probe server %s : %d \n",
		inet_ntoa(host_addr.sin_addr), remote_port);
	if (connect(sockfd, (struct sockaddr *)&host_addr, 
		sizeof(struct sockaddr)) == -1){
	    perror("connect");
	    return NULL;
	}
	printf("success\n");

	// Connect the SSL socket
	ssl=SSL_new(ctx);
	sbio=BIO_new_socket(sockfd, BIO_NOCLOSE);
	SSL_set_bio(ssl,sbio,sbio);
	if (SSL_connect(ssl)<=0){
	     berr_exit("Error in the SSL connection");
	     return NULL;
  	}

	X509* peerCertificate;

	if(SSL_get_verify_result(ssl) == X509_V_OK){
		printf("verify is OK! \n");
		peerCertificate = SSL_get_peer_certificate(ssl);
	} else {
		printf("verify failed \n");
		ERR_print_errors(bio_err);
	}

	return ssl;
}


void contact_probe_server (notary_header *hdr, int msg_len,
		SSL *ssl_connection) {

	// Send the message
	char buf[MAX_PACKET_LEN];


	printf("Contacting server with %d bytes\n", msg_len);
	int offset = SSL_write(ssl_connection, hdr, msg_len);
	if (offset == -1){
	    perror("ssl write");
	    return;
	}

	printf("Wrote %d bytes on the SSL socket, waiting for response \n", 
		offset);

	// Read Reply
	int num_read = SSL_read(ssl_connection, buf, MAX_PACKET_LEN);
	if (num_read == -1){
	    perror("ssl recv");
	    return;
	}

	printf("received %d bytes \n", num_read);

	
	hdr = (notary_header*) buf;
	printf("reply is version %d \n", hdr->version);
}

