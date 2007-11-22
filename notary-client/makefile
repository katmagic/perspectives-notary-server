
SSL_DIR=/usr/local/ssl
LIBS=  -lstdc++ -ldl -lz  -lssl -lcrypto
CFLAGS=-g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99 -I../common/ -I$(SSL_DIR)/include
LIBNOTARYCLIENT_OBJS = notary_local.o contact_notary.o client_policy.o

libnotaryclient.a: $(LIBNOTARYCLIENT_OBJS)
	$(AR) rv $@ $(LIBNOTARYCLIENT_OBJS)

.c.o:
	gcc $(CFLAGS) -c $<

clean:
	rm -rf *.o libnotaryclient.a
