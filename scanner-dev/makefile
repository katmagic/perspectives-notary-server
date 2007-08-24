
SSH_SRC_DIR=../openssh-4.4p1
CARES_SRC_DIR=../c-ares-1.4.0
SSL_DIR=/usr/local/ssl
LIBS=  -lstdc++ -ldl -lz  -lssl -lcrypto
LDFLAGS=-L. -L$(SSL_DIR)/lib -L$(MYSQL_DIR)/lib
CFLAGS=-g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99
CPPFLAGS=-I$(SSH_SRC_DIR) -I/usr/include/mysql/ -I$(SSL_DIR)/include -I$(CARES_SRC_DIR) -DHAVE_CONFIG_H
OBJECTS=ssh-keyscan.o patricia.o mysql_storage.o net_util.o fast_dns.o

default: $(OBJECTS)
	gcc -g $(OBJECTS) $(LDFLAGS) -lssh -lopenbsd-compat -lssh $(LIBS) -lmysqlclient -lcares -o scanner 

db_test: mysql_storage.o
	gcc -g mysql_storage.o $(LDFLAGS) -lssh -lopenbsd-compat -lssh $(LIBS) -lmysqlclient -o mysql_db_test

exception_test: patricia.o 
	gcc patricia.o $(LDFLAGS) -lmysqlclient -o exception_test	

dns_test: fast_dns.o net_util.o 
	gcc fast_dns.o net_util.o $(LDFLAGS) -lcares -o dns_test	

.c.o:
	gcc $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o scanner mysql_db_test exception_test
