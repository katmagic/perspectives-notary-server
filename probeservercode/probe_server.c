

#include <openssl/ssl.h> 
#include <openssl/rand.h>
#include <openssl/x509.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/pem.h>

#include "../common.h"
#include <sqlite3.h>
#include "probe_server.h"
#include "ssh-keyscan.h"
#include "xmalloc.h"
#include "db_storage.h"


unsigned int notary_debug = DEBUG_NONE;

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

    DPRINTF(DEBUG_SSL,"Successfully loaded private key and certificate\n");
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
 
	DPRINTF(DEBUG_INFO,"waiting for incoming connections on %s : %d \n",
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
	DPRINTF(DEBUG_INFO,"Received connection from %s : %d \n", 
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
	
	DPRINTF(DEBUG_SOCKET, "adding socket = %d to list \n", tmp->sock);
	list_add(&(tmp->list), &(head->list));
}


// returns 1 if this header was able to be processed by 
// the ssh-keyscan layer.  
int process_request(sqlite3* db, conn_node *conn,notary_header *hdr) {

	char* data = (char*)(hdr + 1);
	int name_len = ntohs(hdr->name_len);

	if(name_len > 1024) {
		DPRINTF(DEBUG_ERROR,
		"Ignoring request because domain name > 1024 bytes\n");
		return 1; 
	}
	char *host = (char*) malloc(name_len);
	
	memcpy(host, data,name_len);

        struct timeval t;
        gettimeofday(&t,NULL);
        int cur_secs = t.tv_sec;
	// TODO: need to take key-type into consideration
	int last_probe_time = get_last_probe_time(db, host);
	int diff = cur_secs - last_probe_time;

	printf("last probe was %.1f minutes ago \n",SEC2MIN(diff)); 	


	uint16_t service_type = ntohs(hdr->service_type);
	uint16_t port = ntohs(hdr->service_port);
	DPRINTF(DEBUG_INFO, "Handing %s to do_host with service type %d \n", 
			host, service_type);
	return do_single_probe(host, service_type, port, conn);
}


void process_socket_data(sqlite3* db, conn_node *conn) { 

	do {
		int bytes_read = SSL_read(conn->ssl, conn->buf + conn->offset, 
			MAX_PACKET_LEN - conn->offset);
		DPRINTF(DEBUG_SOCKET, "read %d bytes \n", bytes_read);

		if(bytes_read == 0) {
			DPRINTF(DEBUG_ERROR, 
				"connection closed on socket %d \n", conn->sock);
			SSL_shutdown(conn->ssl);
			close(conn->sock);
			list_del(&(conn->list));
			free(conn);
			return;
		}

		int ret_val = SSL_get_error(conn->ssl, bytes_read);
		
		if(ret_val == SSL_ERROR_ZERO_RETURN) {
			DPRINTF(DEBUG_ERROR, "Connection has been closed remotely\n");
			return;
		} else if(ret_val == SSL_ERROR_SYSCALL) {
			perror("Socket Syscall error");
			return;
		}else if(ret_val != SSL_ERROR_NONE) {
    			DPRINTF(DEBUG_ERROR | DEBUG_SSL, "SSL_read returned error. \n");
    			ERR_print_errors(bio_err);
			return;
		}

		int hdr_len = sizeof(notary_header);
		conn->offset += bytes_read;
		if(conn->offset >= hdr_len) {
			notary_header *hdr = (notary_header*) conn->buf;
			uint16_t pkt_len = ntohs(hdr->total_len);
			if(pkt_len <= conn->offset) {
				// loop until the lower layer accepts
				// another connection
				while(!process_request(db, conn, hdr)) {}
				// pkt_len bytes consumed
				memmove(conn->buf, conn->buf + pkt_len,
				 MAX_PACKET_LEN - pkt_len);
				conn->offset -= pkt_len;
			}else {
				DPRINTF(DEBUG_SOCKET,
					"%d bytes has header but not all %d bytes \n", 
					conn->offset, pkt_len);
			}
		}else {
			DPRINTF(DEBUG_SOCKET,
			"%d bytes is not enough for header \n", conn->offset);
		}
	} while(SSL_pending(conn->ssl));
}

void store_probe_result(sqlite3* db, ssh_key_holder *key_holder,
			int time) {

	if(key_holder->key == NULL) {
		DPRINTF(DEBUG_ERROR, "Key is null. No probe stored. \n");
		return;
	}

	IF_DEBUG(DEBUG_MESSAGE) {
		printf("putting key in DB \n");
		key_write(key_holder->key, stdout);
		fputs("\n", stdout);
	}

	store_ssh_probe_result(db, key_holder->name, 
			key_holder->ip_addr, key_holder->key, time);
	
}

void send_reply(sqlite3* db, char *hostname, uint16_t port, 
		uint16_t key_type, SSL* ssl , int sock) {

	ssh_msg_list* reply_list = lookupName(db, hostname,
						port, key_type);

	struct list_head *pos;
	ssh_msg_list* cur;
	list_for_each(pos, &reply_list->list) {
		cur = list_entry(pos, ssh_msg_list, list);
	
		notary_header* hdr = cur->hdr;
		int total_len = ntohs(hdr->total_len);
/*		char* data = (char*)hdr;
		for(int i = 0; i < total_len; i = i + 4) {
			printf("%d %d %d %d \n", data[i],
				data[i+1], data[i+2], data[i+3]);
		}
*/
        	int offset = SSL_write(ssl, hdr, total_len);
        	if (offset == -1){
            		perror("ssl write");
            		return;
        	}
		DPRINTF(DEBUG_INFO, "Replied on sock = %d with %d bytes (%d sent)\n", 
			sock, total_len, offset);
		
		free(hdr);
		
//		list_del(pos); 
//		free(cur);
	}
	DPRINTF(DEBUG_INFO,
		"done with all replies for %s, closing connection \n", 
		hostname);
}

// returns maxfd + 1
int setup_readfds(fd_set *readfds, conn_node *head, int server_sock) {
	int max_fd = server_sock;
	FD_ZERO(readfds);	
        DPRINTF(DEBUG_ALL, "set readfs for server sock = %d \n", server_sock);
	FD_SET(server_sock, readfds);	
	struct list_head* pos;
	conn_node* tmp;

	list_for_each(pos, &(head->list)) {
		tmp = list_entry(pos, conn_node, list);
		if(tmp->sock > max_fd) max_fd = tmp->sock;
		FD_SET(tmp->sock , readfds);
                DPRINTF(DEBUG_ALL,
                        "set readfs for client sock = %d \n", tmp->sock);

	}
	return max_fd + 1;
}

int main(int argc, char** argv) {
	conn_node conn_list, *tmp;
	if(argc != 3) {
		fprintf(stderr, "usage: probe_server <port> <db-filename>\n");
		exit(1);
	}

	uint16_t port = atoi(argv[1]);	

	INIT_LIST_HEAD(&conn_list.list);	
	
	int server_sock;
	ssh_key_holder ssh_keys[NUM_HOLDERS];
	fd_set readfds;
	struct timeval select_timeout;

	init_scankeys();
	sqlite3* db = db_init(argv[2]);
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
                                DPRINTF(DEBUG_SOCKET,"new client! \n");
				acceptIncomingSSLClient(server_sock, &conn_list);
			}
			
			struct list_head *pos, *q;
			list_for_each_safe(pos, q, &(conn_list.list)) {
				tmp = list_entry(pos, conn_node, list);
				if(FD_ISSET(tmp->sock , &readfds)) {
					process_socket_data(db, tmp);
				}
			}
		}else {
                        DPRINTF(DEBUG_ALL, "select returned nothing \n");
                }


		int num_holders_used = conloop(ssh_keys, NUM_HOLDERS);
	
		if(num_holders_used > 0) {	
		
			struct timeval cur_time;
			gettimeofday(&cur_time, NULL);
			int time = (uint32_t) cur_time.tv_sec;
			for(int i = 0; i < num_holders_used; i++) {
				ssh_key_holder *h = (&ssh_keys[i]);
				store_ssh_probe_result(db, h->name, 
					h->ip_addr, h->key, time) ;
	
				send_reply(db,h->name, h->port, h->key_type,
						h->conn->ssl, h->conn->sock);
				SSL_shutdown(h->conn->ssl);
				close(h->conn->sock);
				list_del(&(h->conn->list));
				free(h->conn);
			}
		}

	
  	} // end while

	db_close(db);
	close(server_sock);
}



