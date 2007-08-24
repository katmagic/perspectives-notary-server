
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



char *ip_2_str(uint32_t ip) {
  return inet_ntoa(*(struct in_addr*)&ip);
}

uint32_t str_2_ip(char* ip_str) {
  int ip;
  inet_aton(ip_str, (struct in_addr*)&ip);
  return ip;
}

// expects IP to be in network byte order
// note: caller should free memory!
// return 0 on success
int getDNSFromIP(uint32_t ip_addr, char** name) {
  struct hostent *h;

  h = gethostbyaddr((char*)&ip_addr, sizeof(uint32_t),AF_INET);

  if(h == NULL) {
    *name = strdup(ip_2_str(ip_addr));
    return 1;
  } else {
    *name = strdup(h->h_name);
    return 0;
  }
}

int getDNSFromIPstr(char *ip_str, char** name) {
  return getDNSFromIP(str_2_ip(ip_str), name);
}

// return 0 on success
int getIPFromDNS(char *dns_name, uint32_t* addr_out) {
  struct hostent *h;

  if( (h = gethostbyname2(dns_name,AF_INET)) == NULL) {
    printf("gethostbyname error for %s : %s \n",
            dns_name, hstrerror(h_errno));
    return h_errno;
  }
//  printf("canonical: %s \n", h->h_name);

//  char** pptr;
//  for(pptr = h->h_aliases; *pptr != NULL; pptr++)
//    printf("\talias: %s \n", *pptr);
  
  *addr_out = *(uint32_t*)*(h->h_addr_list);
//  printf("IP: %s \n", ip_2_str(*addr_out));
 
  return 0;
}

char *getConfirmedDNSFromIP(uint32_t ip_addr) {
  char *dns_name;
  int error = getDNSFromIP(ip_addr, &dns_name);
  if(error) goto failed;
    
  uint32_t ip_again;
  error = getIPFromDNS(dns_name, &ip_again);
  if(error || ip_addr != ip_again) goto failed;

  return dns_name;
      
  failed:
      free(dns_name);
      return strdup(ip_2_str(ip_addr));
}


/*
int main(int argc, char** argv) {

  if(argc == 2)
    printf("confirmed: %s \n", getConfirmedDNSFromIP(str_2_ip(argv[1])));
   // printf("%s \n", getDNSFromIPstr(argv[1]));
  return 0;
}
*/

