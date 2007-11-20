
SSL_DIR=/usr/local/ssl
SSH_SRC_DIR=../openssh-4.4p1
CPPFLAGS= -g -O2 -Wall -fno-strict-aliasing -I$(SSH_SRC_DIR) -I/usr/include/mysql/ -I$(SSL_DIR)/include -DHAVE_CONFIG_H


LIBNOTARYCOMMON_OBJS = mysql_storage.o notary_util.o net_util.o patricia.o notary_crypto.o bdb_storage.o

libnotarycommon.a: $(LIBNOTARYCOMMON_OBJS)
	$(AR) rv $@ $(LIBNOTARYCOMMON_OBJS)
	echo "Done building libnotarycommon" 

.c.o:
	gcc $(CPPFLAGS) -c $<

clean:
	rm -rf *.o
