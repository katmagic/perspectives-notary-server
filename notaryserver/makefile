SSH_SRC_DIR=../../openssh-4.4p1
OBJECTS= notary_local.o contact_probe_server.o notary_client.o 
LIBS= -lresolv -lstdc++ -lcrypto -lz  -ldl -lssl -lcrypto -lssh -lopenbsd-compat
CC=gcc -g

LDFLAGS=-L. -L/usr/local/ssl/lib
CPPFLAGS=-I$(SSH_SRC_DIR) -I/usr/local/ssl/include -DHAVE_CONFIG_H

default: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS)  $(LIBS) -o notary_client

.c.o: 
	$(CC) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o notary_server notary_client
