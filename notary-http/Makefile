BDB_DIR=/usr/local/BerkeleyDB.4.6/
SSL_DIR=/usr/local/ssl
L1   =  -lstdc++ -lz -lssl -lcrypto -lpthread -ldb-4.6   
L2   =../common/libnotarycommon.a ../notary-client/libnotaryclient.a
LIBS = $(L1) $(L2)
LDFLAGS=-L. -L$(SSL_DIR)/lib -L../common/ -L$(BDB_DIR)/lib 
HEADERS= -I../notary-client -I../common -I$(SSL_DIR)/include -I$(BDB_DIR)/include 
CFLAGS= -g -O2 -I. -Wall -Werror -std=gnu99 $(HEADERS)
OBS= notary_http.o parse.o

all: notary-http

notary-http: $(OBS)
	gcc $(LDFLAGS) $(OBS)  $(LIBS) -ldb-4.6 -o notary_http

static: $(OBS)
	gcc $(LDFLAGS) $(OBS) ../common/libnotarycommon.a ../common/libdb-4.6.a $(LIBS) -o notary_http

.c.o:
	gcc $(CFLAGS) -c $<

clean:
	rm -rf $(OBS) notary_http
