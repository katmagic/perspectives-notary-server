
SSH_SRC_DIR=../openssh-4.4p1
SSL_DIR=/usr/local/ssl
LIBS=  -lstdc++ -ldl -lz  -lssl -lcrypto -lmysqlclient -lssh
LDFLAGS=-L. -L../lib -L$(SSL_DIR)/lib -L$(MYSQL_DIR)/lib -L$(SSH_SRC_DIR)
CFLAGS=-g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99
CPPFLAGS=-g -O2 -Wall -I$(SSH_SRC_DIR) -I../common -I/usr/include/mysql/ -I$(SSL_DIR)/include -DHAVE_CONFIG_H
LIBNOTARYCLIENT_OBJS = notary_client.o

libnotaryclient.a: $(LIBNOTARYCLIENT_OBJS)
	$(AR) rv $@ $(LIBNOTARYCLIENT_OBJS)

.c.o:
	gcc $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o test_client
