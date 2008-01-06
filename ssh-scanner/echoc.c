/*
** echoc.c -- the echo client for echos.c; demonstrates unix sockets
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "echo_socket"

int main(void)
{
    int s, t, len;
    struct sockaddr_un remote;
    char str[100];

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected.\n");

   
    char *dns_name = "gs5025.sp.cs.cmu.edu";
    int name_len = strlen(dns_name);
    int key_len = 128;
    char key_buf[128];
    memset(key_buf, 'A', 128);
    key_buf[126] = 'Z';
    key_buf[127] = 0;

    int port = htons(22);
    int ip_addr;
    inet_aton("128.2.134.90", (struct in_addr*)&ip_addr);

    int total_len = name_len +  key_len + 7; // ip-addr,port,null-byte = 7
    char * buf = (char*)malloc(total_len);
    char *ptr = buf;
    memcpy(ptr, dns_name, name_len + 1);
    ptr += name_len + 1;
    memcpy(ptr, &ip_addr, 4);
    ptr += 4;
    memcpy(ptr, &port, 2);
    ptr += 2;
    memcpy(ptr, key_buf, key_len);

    printf("name: %s \n", buf);
    printf("key: %s \n", buf + name_len + 7);

    int n = send(s, buf,total_len , 0);
    if(n == -1) {
       perror("send");
       exit(1);
    }
    printf("Sent %d bytes \n", n);

    free(buf);
    close(s);

    return 0;
}



