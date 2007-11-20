
SSH_SRC_DIR=../openssh-4.4p1
CARES_SRC_DIR=c-ares-1.4.0
SSL_DIR=/usr/local/ssl
LIBS=  -lopenbsd-compat -lssh -lstdc++ -ldl -lz  -lssl -lcrypto -lmysqlclient -lssh ../notary-client/libnotaryclient.a ../common/libnotarycommon.a ../common/libdb-4.6.a -lssh -lopenbsd-compat

LDFLAGS=-L. -L../lib -L$(SSL_DIR)/lib -L$(MYSQL_DIR)/lib -L$(SSH_SRC_DIR)
CFLAGS=-g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99 -I$(SSH_SRC_DIR) -I../common -I../notary-client -I/usr/include/mysql/ -I$(SSL_DIR)/include -DHAVE_CONFIG_H

simple_client: simple_client.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

load_test_client: load_test_client.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

db_search: db_search.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

signature_util: signature_util.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

mysql_bdb_convert: mysql_bdb_convert.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

update_timespans_test: update_timespans_test.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

batch_dns: batch_dns.o 
	gcc $(LDFLAGS) $? $(LIBS) -o $@

.c.o:
	gcc $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o batch_dns update_timespans_test db_search mysql_bdb_convert load_test_client signature_util simple_client
