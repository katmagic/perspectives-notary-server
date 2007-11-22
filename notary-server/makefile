
SSL_DIR=/usr/local/ssl
LIBS=  -lstdc++ -ldl -lz -lssl -lcrypto -lpthread -ldb-4.6   
LDFLAGS=-L. -L../lib -L$(SSL_DIR)/lib -L../common/
CFLAGS= -g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99 -I../common -I$(SSL_DIR)/include

timespans: server.o
	gcc $(LDFLAGS) server.o ../common/libnotarycommon.a $(LIBS) -o notary_server

.c.o:
	gcc $(CFLAGS) -c $<

clean:
	rm -rf *.o notary_server
