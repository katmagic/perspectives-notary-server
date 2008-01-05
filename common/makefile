
SSL_DIR=/usr/local/ssl
CPPFLAGS= -g -O2 -Wall -fno-strict-aliasing -I$(SSL_DIR)/include
LIBNOTARYCOMMON_OBJS = file_list_convert.o notary_util.o net_util.o notary_crypto.o bdb_storage.o patricia.o flex_queue.o

libnotarycommon.a: $(LIBNOTARYCOMMON_OBJS)
	$(AR) rv $@ $(LIBNOTARYCOMMON_OBJS)
	echo "Done building libnotarycommon" 

.c.o:
	gcc $(CPPFLAGS) -c $<

clean:
	rm -rf *.o libnotarycommon.a
