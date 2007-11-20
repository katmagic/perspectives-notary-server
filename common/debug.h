#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>  /* for perror */
#include <sys/types.h>

extern unsigned int notary_debug;
#define DPRINTF(level, fmt, args...) \
        do { if (notary_debug & (level)) fprintf(stderr, fmt , ##args ); } while(0);
#define DEBUG_PERROR(errmsg) \
        do { if (notary_debug & DEBUG_ERRS) perror(errmsg); } while(0);
#define IF_DEBUG(level) \
	if(notary_debug & (level))

#define DEBUG_NONE      0x00    // No debugging
#define DEBUG_ERROR 	0x01
#define DEBUG_INFO      0x02    // Verbose info + error reporting
#define DEBUG_SOCKET   0x04    // Socket Errors + Info
#define DEBUG_SSL 0x08    // SSL Errors + Info
#define DEBUG_DATABASE      0x10    // Database errors + info
#define DEBUG_MESSAGE	 0x20  // Information about Packet Contents
#define DEBUG_CRYPTO     0x40  // 
#define DEBUG_ALL  0xffffffff

#ifdef __cplusplus
extern "C" {
#endif
  int set_debug(char *arg);  /* Returns 0 on success, -1 on failure */
#ifdef __cplusplus
}
#endif

#endif /* _DEBUG_H_ */
