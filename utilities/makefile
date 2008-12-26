BDB_DIR=/usr/local/BerkeleyDB.4.6/
SSL_DIR=/usr/local/ssl
LIBS=  ../notary-client/libnotaryclient.a ../common/libnotarycommon.a -lpthread -lstdc++  -lz  -lssl -lcrypto -ldb-4.6 

LDFLAGS=-L. -L$(BDB_DIR)/lib -L$(SSL_DIR)/lib -L../common/
CFLAGS=-g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99 -I../common -I../notary-client -I$(SSL_DIR)/include -I$(BDB_DIR)/include

all: gen_svg test_policy_fake request_scan db2file file2db db_multiaccess_test test_policy full_client simple_client load_test_client db_search signature_util db_speed_test update_timespans_test gen_mozilla_sig

gen_svg: gen_svg.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

test_policy_fake: test_policy_fake.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

db2file: db2file.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

file2db: file2db.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

db_multiaccess_test: db_multiaccess_test.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

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
	
request_scan: request_scan.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

gen_mozilla_sig: gen_mozilla_sig.o
	gcc $(LDFLAGS) $? $(LIBS) -o $@

.c.o:
	gcc -g $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o gen_svg request_scan full_client batch_dns update_timespans_test db_search db_speed_test load_test_client signature_util simple_client gen_mozilla_sig
