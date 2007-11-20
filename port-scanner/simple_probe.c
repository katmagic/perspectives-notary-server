#define u8 char
#define u16 short
#define u32 int

/*u8 *build_tcp_raw(const struct in_addr *source, const struct in_addr *victim,
                  int ttl, u16 ipid, u8 tos, bool df,		  u8 *ipopt, int ipoptlen, 
		  u16 sport, u16 dport,
		  u32 seq, u32 ack, u8 reserved, u8 flags, u16 window, u16 urp,
		  u8 *tcpopt, int tcpoptlen,
		  char *data, u16 datalen, u32 *outpacketlen) {
*/

/* If this is NOT a ping probe, set pingseq to 0.  Otherwise it will be the
   ping sequence number (they start at 1).  The probe sent is returned. */


