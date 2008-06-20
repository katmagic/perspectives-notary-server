
#include "common.h"
#include "keyscan_util.h"
#include "net_util.h"

unsigned int notary_debug = DEBUG_ERROR | DEBUG_INFO; 

int main(int argc, char**argv) {

  if(argc != 2) {
    printf("usage: <file-of-serviceids>\n");
    exit(1); 
  }

        char buf[1024];
	FILE *f;
	assert(argv[1]);

	f = fopen(argv[1], "r");
	if(f == NULL) {
		DPRINTF(DEBUG_ERROR,"invalid to_probe file %s \n", argv[1]);
		exit(1);
	}
        int total = 0; 
	while(fgets(buf, 1024,f) != NULL) {
		if(*buf == '\n') continue;
		int size = strlen(buf);
		buf[size - 1] = 0x0; // replace '\n' with NULL
                DPRINTF(DEBUG_INFO, "Loaded service-id = '%s'\n",buf);
                sendToUnixSock(NEW_REQUEST_SOCK_NAME, buf, size);
                ++total; 
        }		
        DPRINTF(DEBUG_INFO, "Requested %d total probes \n", total); 
}
