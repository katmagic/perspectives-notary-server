
SSH_SRC_DIR=../openssh-4.4p1
OBJECTS=probe_server.o ssh-keyscan.o db_storage.o background_probing.o libsqlite3.a
LIBS=  -lstdc++ -ldl -lz  -lssl -lcrypto
LDFLAGS=-L. -L/usr/local/ssl/lib
CFLAGS=-g -O2 -I. -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99
CPPFLAGS=-I$(SSH_SRC_DIR) -I/usr/local/ssl/include -DHAVE_CONFIG_H

server: $(OBJECTS)
	gcc -g $(OBJECTS) $(LDFLAGS) -lssh -lopenbsd-compat -lssh $(LIBS) -o probe_server

bg_probe_test: bg_probe_test.o $(OBJECTS)
	gcc -g bg_probe_test.o db_storage.o libsqlite3.a ssh-keyscan.o background_probing.o $(LDFLAGS) -lsqlite3 -lopenbsd-compat -lssh -lssl -lcrypto $(LIBS) -o bg_probe_test

.c.o:
	gcc $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o probe_server db_util
