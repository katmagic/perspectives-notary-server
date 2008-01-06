/*
** echos.c -- the echo server for echoc.c; demonstrates unix sockets
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCK_PATH "echo_socket"

void handle_connection(int s) {
        int n = -1, t, s2;
        struct sockaddr_un remote;
        char buf[1024];

        printf("Waiting for a connection...\n");
        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
            perror("accept");
            exit(1);
        }

        printf("Connected.\n");

        int so_far = 0;
        while(n != 0) { 
          n = recv(s2, buf + so_far, 1024 - so_far, 0);
          if (n < 0){ 
            perror("recv");
            break;
          }
          so_far += n;
        } 
            
        printf("read %d bytes \n", so_far);
        printf("name: %s \n", buf);
        int name_len = strlen(buf);
        int key_len = n - name_len - 1;
        char *addr_ptr = buf + name_len + 1;
       
        unsigned short port = ntohs(*(unsigned short*) (addr_ptr + 4));
        printf("addr = %s port = %d \n", inet_ntoa(*(struct in_addr*)addr_ptr), port);

        printf("key: %s \n", addr_ptr + 6);

        close(s2);

}



int main(void)
{
    int s, len;
    struct sockaddr_un local;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }

    fd_set readset;
    int result;
    struct timeval t;
    t.tv_sec = 0;
    t.tv_usec = 0;
    while(1) {
      FD_ZERO(&readset);
      FD_SET(s, &readset);
      result = select(s + 1, &readset, NULL, NULL, &t); 

      if(result > 0) {
        if(FD_ISSET(s, &readset)) {
            handle_connection(s);
        }
      }else if(result < 0) {
          perror("select error: ");
      }
      printf("sleeping... \n");
      sleep(10);
    }

    return 0;
}



