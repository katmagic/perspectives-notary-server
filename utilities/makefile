
SSL_DIR=/usr/local/ssl
LIBS=  -lpthread -lstdc++ -ldl -lz  -lssl -lcrypto ../notary-client/libnotaryclient.a ../common/libnotarycommon.a ../common/libdb-4.6.a

LDFLAGS=-L. -L../lib -L$(SSL_DIR)/lib -L../common/
CFLAGS=-g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99 -I../common -I../notary-client -I$(SSL_DIR)/include

test_policy: test_policy.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

full_client: full_client.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

simple_client: simple_client.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

load_test_client: load_test_client.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

db_search: db_search.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

signature_util: signature_util.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

db_speed_test: db_speed_test.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

update_timespans_test: update_timespans_test.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@


.c.o:
	gcc $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o full_client batch_dns update_timespans_test db_search db_speed_test load_test_client signature_util simple_client
