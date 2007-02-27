
LIBS= -lssl libsqlite3.a -lstdc++  
OBJECTS= notary_server.o contact_probe_server.o 
CC=g++ -g -Wno-deprecated

server: notary_server.o contact_probe_server.o
	$(CC) $(LIBS) $(OBJECTS) -o notary_server

client: notary_client.o
	$(CC) notary_client.o -o notary_client	

clean:
	rm -rf *.o notary_server notary_client
