
SSH_SRC_DIR=../openssh-4.4p1
CARES_SRC_DIR=c-ares-1.4.0
SSL_DIR=/usr/local/ssl
LIBS=  -lstdc++ -ldl -lz  -lssl -lcrypto -lmysqlclient -lssh
LDFLAGS=-L. -L../lib -L$(SSL_DIR)/lib -L$(MYSQL_DIR)/lib -L$(SSH_SRC_DIR)
CFLAGS= -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99
CPPFLAGS=-g -O2 -Wall -I$(SSH_SRC_DIR) -I../common -I/usr/include/mysql/ -I$(SSL_DIR)/include -I../udns-0.0.9/ -I$(CARES_SRC_DIR) -DHAVE_CONFIG_H
OBJECTS=ssh-keyscan.o patricia.o mysql_storage.o net_util.o fast_dns.o

timespans: server.o
	gcc $(LDFLAGS) -lopenbsd-compat -lssh $(LIBS) server.o ../common/libnotarycommon.a ../common/libdb-4.6.a -lssh -lopenbsd-compat -o notary_server

.c.o:
	gcc $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o notary_server
