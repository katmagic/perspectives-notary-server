
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/time.h>
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
#include "xmalloc.h"

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
      


void init_serversock(uint16_t port, int* server_sock) {
	struct sockaddr_in server_addr;

	if ((*server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	    perror("socket creation");
	    exit(-1);
	}

	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	if (bind(*server_sock, (struct sockaddr *) 
	   &server_addr,sizeof(server_addr)) < 0){ 
              	perror("ERROR on binding");
		exit(-1);
	}
 
	listen(*server_sock,5);
 
	printf("waiting for incoming connections on %s : %d \n",
		inet_ntoa(server_addr.sin_addr), port);
}

void acceptIncomingSSLClient(int server_sock, conn_node *head) {
	struct sockaddr_in client_addr;
	int addrlen = sizeof(struct sockaddr_in);
	SSL *ssl;
	BIO *sbio;
	conn_node* tmp;
        int client_sock = accept(server_sock, 
              	(struct sockaddr *) &client_addr, &addrlen);
        if (client_sock < 0) {
             	perror("ERROR on accept");
		exit(-1);
	}
	printf("Received connection from %s : %d \n", 
		inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));	

	// Build the SSL context
	SSL_CTX *ctx = initialize_ctx(KEYFILE, CERTFILE);
	
	sbio= BIO_new_socket(client_sock, BIO_NOCLOSE);
	BIO_set_nbio(sbio, 1); // set sockets to non-blocking
	ssl=SSL_new(ctx);
	SSL_set_bio(ssl,sbio,sbio);
	
	if (SSL_accept(ssl)<=0){
    		ERR_print_errors(bio_err);
	     	return;
	}
	
 	tmp = (conn_node*) malloc(sizeof(conn_node));
	tmp->sock = client_sock;
	tmp->ssl = ssl;
	tmp->offset = 0;
	
	printf("adding socket = %d to list \n", tmp->sock);
	list_add(&(tmp->list), &(head->list));
}


// returns 1 if this header was able to be processed by 
// the ssh-keyscan layer.  
int process_request(conn_node *conn,notary_header *hdr) {

	printf("processing request\n");
	char* data = (char*)(hdr + 1);
	printf("data: %s \n", data);
	int name_len = ntohs(hdr->name_len);

	if(name_len > 1024) {
		printf("Ignoring request because domain name > 1024 bytes\n");
		return 1; 
	}
	char *host = (char*) malloc(name_len);
	
	memcpy(host, data,name_len);
	printf("host: %s \n", host);
	uint16_t service_type = ntohs(hdr->service_type);
	uint16_t port = ntohs(hdr->service_port);
	printf("Handing %s to do_host with service type %d \n", host, service_type);
	return do_single_probe(host, service_type, port, conn->ssl, conn->sock);
}


void process_socket_data(conn_node *conn) { 

	do {
		int bytes_read = SSL_read(conn->ssl, conn->buf + conn->offset, 
			MAX_PACKET_LEN - conn->offset);
		printf("read %d bytes \n", bytes_read);

		if(bytes_read == 0) {
			printf("connection closed on socket %d \n", conn->sock);
			SSL_shutdown(conn->ssl);
			close(conn->sock);
			list_del(&(conn->list));
			free(conn);
			return;
		}

		int ret_val = SSL_get_error(conn->ssl, bytes_read);
		
		printf("SSL get-error: %d \n", ret_val); 

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

		int hdr_len = sizeof(notary_header);
		conn->offset += bytes_read;
		if(conn->offset >= hdr_len) {
			notary_header *hdr = (notary_header*) conn->buf;
			uint16_t pkt_len = ntohs(hdr->total_len);
			if(pkt_len <= conn->offset) {
				// loop until the lower layer accepts
				// another connection
				while(!process_request(conn, hdr)) {}
				// pkt_len bytes consumed
				memmove(conn->buf, conn->buf + pkt_len,
				 MAX_PACKET_LEN - pkt_len);
				conn->offset -= pkt_len;
			}else {
				printf("%d bytes has header but not all %d bytes \n", 
					conn->offset, pkt_len);
			}
		}else {
			printf("%d bytes is not enough for header \n", conn->offset);
		}
	} while(SSL_pending(conn->ssl));
}


void send_probe_reply(ssh_key_holder* key_info, int time) {

	if(key_info->key == NULL) {
		fprintf(stderr, "Key is null, sending no reply \n");
		return;
	}

	key_write(key_info->key, stdout);
	fputs("\n", stdout);
	
	u_char* blob;
	int blob_size = 0;
	key_to_blob(key_info->key, &blob, &blob_size);
	printf("Got blob of size %d \n", blob_size);
	
	int key_data_len = sizeof(ssh_key_info) + blob_size;
	int name_len = strlen(key_info->name) + 1;
	int total_len = key_data_len + name_len + sizeof(notary_header);
	notary_header* hdr = (notary_header*) calloc(total_len,1);
	
        hdr->version = 1;
        hdr->msg_type = TYPE_FETCH_REPLY_FINAL;
        hdr->total_len = htons(total_len);
	hdr->name_len = htons(name_len);
        hdr->service_type = htons(key_info->key_type);
        hdr->service_port = htons(key_info->port);
        char* data = (char*) (hdr + 1);
        memcpy(data, key_info->name , name_len);
	data += name_len;
	ssh_key_info* ssh_info = (ssh_key_info*)data;
	ssh_info->key_type = htons(key_info->key_type);
	ssh_info->key_len_bytes = htons(blob_size);
	ssh_info->ip_addr = key_info->ip;
	ssh_info->time_observed = htonl(time);
	printf("key type = %d key_size = %d \n", 
		ntohs(ssh_info->key_type), ntohs(ssh_info->key_len_bytes));

	data = (char*) (ssh_info + 1);  
	// copy key data over
	memcpy(data, blob, blob_size);	
	xfree(blob);

	printf("Replying on sock = %d with %d bytes\n", key_info->client_sock, total_len);
        int offset = SSL_write(key_info->client_ssl, hdr, total_len);
        if (offset == -1){
            perror("ssl write");
            return;
        }

        printf("Wrote %d bytes on the SSL socket\n", offset);

}

// returns maxfd + 1
int setup_readfds(fd_set *readfds, conn_node *head, int server_sock) {
	int max_fd = server_sock;
	FD_ZERO(readfds);	
	FD_SET(server_sock, readfds);	
	struct list_head* pos;
	conn_node* tmp;

	list_for_each(pos, &(head->list)) {
		tmp = list_entry(pos, conn_node, list);
		printf("setting readfd set for %d \n", tmp->sock);
		if(tmp->sock > max_fd) max_fd = tmp->sock;
		FD_SET(tmp->sock , readfds);
	}
	return max_fd + 1;
}

int main(int argc, char** argv) {
	conn_node conn_list, *tmp;
	if(argc != 2) {
		fprintf(stderr, "usage: probe_server <port>\n");
		exit(1);
	}

	uint16_t port = atoi(argv[1]);	
	INIT_LIST_HEAD(&conn_list.list);	
	
	int server_sock;
	ssh_key_holder ssh_keys[NUM_HOLDERS];
	fd_set readfds;
	struct timeval select_timeout;

	init_scankeys();

	init_serversock(port, &server_sock);

	// loop to keep reading requests sent by notary server,
	// dispatch them to be probed, and then reply to notary
	// server once probing is done.
	while(1) {
		// need to reset each time on linux
		select_timeout.tv_sec = 1;
		select_timeout.tv_usec = 0;
	
		int max_fd = setup_readfds(&readfds, &conn_list, server_sock);

		int num_fds = select(max_fd, &readfds, NULL, NULL,
					&select_timeout);
		if(num_fds > 0) {
			if(FD_ISSET(server_sock, &readfds)) {
				printf("new client connection \n");
				acceptIncomingSSLClient(server_sock, &conn_list);
			}
			
			struct list_head *pos, *q;
			list_for_each_safe(pos, q, &(conn_list.list)) {
				tmp = list_entry(pos, conn_node, list);
				printf("testing readfd set for %d \n", tmp->sock);
				if(FD_ISSET(tmp->sock , &readfds)) {
					printf("reading from client %d \n", 
							tmp->sock);
					process_socket_data(tmp);

				}
			}
		}else {
			printf("Select returned, no fds set...\n");
		}

		int num_holders_used = conloop(ssh_keys, NUM_HOLDERS);
	
		if(num_holders_used > 0) {	
			printf("***** main server loop got %d holders back! ****** \n", num_holders_used);
		
			struct timeval cur_time;
			gettimeofday(&cur_time, NULL);
			int time = (uint32_t) cur_time.tv_sec;
			for(int i = 0; i < num_holders_used; i++) {
				send_probe_reply(&ssh_keys[i], time);
			}
		}

	
  	} // end while

	close(server_sock);
}



