BDB_DIR=/usr/local/BerkeleyDB.4.6/
SSL_DIR=/usr/local/ssl
LIBS=  ../common/libnotarycommon.a -lpthread -lstdc++ -lz  -lssl -lcrypto  
LDFLAGS=-L. -L$(BDB_DIR)/lib -L$(SSL_DIR)/lib -L../common/
CFLAGS=-g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99 -I../common -I$(SSL_DIR)/include -I$(BDB_DIR)/include


notary_scanner: notary_scanner.o 
	gcc $(LDFLAGS) $? $(LIBS) -ldb-4.6 -o $@

static: notary_scanner.o 
	gcc $(LDFLAGS) $? $(LIBS) ../common/libdb-4.6.a -o notary_scanner

empty: empty.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

.c.o:
	gcc $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o notary_scanner
