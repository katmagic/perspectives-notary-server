SSH_SRC_DIR=/afs/cs.cmu.edu/user/dwendlan/multissh/openssh-4.4p1
OBJECTS= notary_local.o contact_probe_server.o notary_client.o 
LIBS= -lefence -lresolv -lstdc++ -lcrypto -lutil -lz -lnsl  -ldl -lcrypt -lssl -lcrypto
CC=gcc -g

LDFLAGS=-L. -L/usr/local/ssl/lib
CPPFLAGS=-I$(SSH_SRC_DIR) -I/usr/local/ssl/include -DHAVE_CONFIG_H

default: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -lssh -lopenbsd-compat -lssh $(LIBS) -o notary_client

.c.o: 
	$(CC) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o notary_server notary_client
