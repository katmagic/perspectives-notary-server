CXX   = g++
CPPFLAGS +=     -fno-rtti -g              \
		-fno-exceptions        \
		-bundle -flat_namespace -undefined suppress
 
# Change these 4 defines according the env. The last 3 defaults are according
# to the repository.
COPY = /bin/cp
GECKO_SDK_PATH = ../gecko-sdk-mac-intel-1.8.1.3
PLUGIN_PATH = ../plugin
NOTARY_CODE_PATH = ../..

XPIDL_PATH = $(GECKO_SDK_PATH)/bin
NOTARY_CLIENT = $(NOTARY_CODE_PATH)/notary-client
NOTARY_COMMON = $(NOTARY_CODE_PATH)/common
OPENSSL_PATH = /usr/local/ssl

# GCC only define which allows us to not have to #include mozilla-config 
# in every .cpp file.  If your not using GCC remove this line and add 
# #include "mozilla-config.h" to each of your .cpp files. 
GECKO_CONFIG_INCLUDE = -include xpcom-config.h 
 
GECKO_DEFINES  = -DXPCOM_GLUE -DPERSPECTIVE
 
 
GECKO_INCLUDES = -I$(GECKO_SDK_PATH)/include -I$(NOTARY_CLIENT) -I$(NOTARY_COMMON)
 
#GECKO_LDFLAGS =  -L$(GECKO_SDK_PATH)/lib -lxpcomglue \
#                 -lnspr4      \
#                 -lplds4      


GECKO_LDFLAGS = -L$(GECKO_SDK_PATH)/lib \
		-L$(GECKO_SDK_PATH)/bin \
		-L$(OPENSSL_PATH)/lib \
	 	-lxpcomglue_s \
	 	-lxpcomglue \
		-lnspr4 -lplds4 -lplc4 -lssl


FILES = psvBadCertListener.cpp psvBadCertListenerModule.cpp $(NOTARY_COMMON)/notary_crypto.c $(NOTARY_CLIENT)/notary_local.c $(NOTARY_COMMON)/net_util.c $(NOTARY_COMMON)/notary_util.c contact_notary.c $(NOTARY_CLIENT)/client_policy.c $(NOTARY_COMMON)/flex_queue.c
#FILES = psvBadCertListener.cpp psvBadCertListenerModule.cpp notary_src/notary_crypto.c

TARGET = Perspectives.so

build: 
	$(XPIDL_PATH)/xpidl -m header -I$(GECKO_SDK_PATH)/idl psvIBadCertHandler.idl
	$(XPIDL_PATH)/xpidl -m typelib -I$(GECKO_SDK_PATH)/idl psvIBadCertHandler.idl
	$(COPY) psvIBadCertHandler.xpt $(PLUGIN_PATH)/components/Perspectives.xpt
	$(CXX) -Os $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CPPFLAGS) $(CXXFLAGS) $(FILES) $(GECKO_LDFLAGS) -o $(TARGET) 
	chmod +x $(TARGET)
#	strip $(TARGET)

#	$(CXX) -Wl,-z,defs -Os -o $(TARGET) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(GECKO_LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(FILES)

 
clean: 
	rm $(TARGET) psvIBadCertHandler.h psvIBadCertHandler.xpt

