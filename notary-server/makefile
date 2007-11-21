
SSL_DIR=/usr/local/ssl
LIBS=  -lstdc++ -ldl -lz  -lssl -lcrypto -lpthread ../common/libnotarycommon.a ../common/libdb-4.6.a 
LDFLAGS=-L. -L../lib -L$(SSL_DIR)/lib -L../common/
CFLAGS= -g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99 -I../common -I$(SSL_DIR)/include

timespans: server.o
	gcc $(LDFLAGS) server.o $(LIBS) -o notary_server

.c.o:
	gcc $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o notary_server
