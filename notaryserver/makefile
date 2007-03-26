SSH_SRC_DIR=../../openssh-4.4p1
LIBOBJECTS= notary_local.o contact_probe_server.o
OBJECTS= $(LIBOBJECTS) notary_client.o
LIBS= -lresolv -lstdc++ -lcrypt -lcrypto -lz  -ldl -lssl -lcrypto -lssh -lopenbsd-compat
CC=gcc -g

LDFLAGS=-L. -L/usr/local/ssl/lib
CPPFLAGS=-I$(SSH_SRC_DIR) -I/usr/local/ssl/include -DHAVE_CONFIG_H

default: $(OBJECTS)
	$(CC)  $(OBJECTS) $(LDFLAGS) -lcrypto -lssl -lssh $(LIBS) -o notary_client

lib: $(LIBOBJECTS)
	ar -cq libnotary.a $(LIBOBJECTS)
.c.o: 
	$(CC) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o libnotary.a notary_server notary_client
