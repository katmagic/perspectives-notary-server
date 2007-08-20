
SSH_SRC_DIR=../openssh-4.4p1
MYSQL_DIR=/usr0/mysql
SSL_DIR=/usr/local/ssl
LIBS=  -lstdc++ -ldl -lz  -lssl -lcrypto
LDFLAGS=-L. -L$(SSL_DIR)/lib -L$(MYSQL_DIR)/lib
CFLAGS=-g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99
CPPFLAGS=-I$(SSH_SRC_DIR) -I$(MYSQL_DIR)/include -I/$(SSL_DIR)/include -DHAVE_CONFIG_H
OBJECTS=ssh-keyscan.o patricia.o mysql_storage.o

default: $(OBJECTS)
	gcc -g $(OBJECTS) $(LDFLAGS) -lssh -lopenbsd-compat -lssh $(LIBS) -lmysqlclient -o scanner 

db_test: mysql_storage.o
	gcc -g mysql_storage.o $(LDFLAGS) -lssh -lopenbsd-compat -lssh $(LIBS) -lmysqlclient -o mysql_db_test

exception_test: patricia.o 
	gcc patricia.o $(LDFLAGS) -lmysqlclient -o exception_test	

.c.o:
	gcc $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o scanner mysql_db_test exception_test
