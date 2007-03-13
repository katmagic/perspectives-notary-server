
SSH_SRC_DIR=/afs/cs.cmu.edu/user/dwendlan/multissh/openssh-4.4p1
OBJECTS=probe_server.o ssh-keyscan.o 
LIBS=-lresolv -lstdc++ -lcrypto -lutil -lz -lnsl  -ldl -lcrypt -lssl -lcrypto
LDFLAGS=-L. -L/usr/local/ssl/lib
CFLAGS=-g -O2 -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -std=gnu99
CPPFLAGS=-I$(SSH_SRC_DIR) -I/usr/local/ssl/include -DHAVE_CONFIG_H



server: $(OBJECTS)
	gcc -g $(OBJECTS) $(LDFLAGS) -lssh -lopenbsd-compat -lssh $(LIBS) -o probe_server

.c.o:
	gcc $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o probe_server
