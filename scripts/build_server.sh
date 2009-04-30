#!/bin/sh


if ! [ -d "notary-server" ]; then
  echo "Error: Script must be run from top of notarycode directory"
  echo "EXITING"
  exit 1
fi

static='' 

if [ $# = 1 ] && [ "$1" = "static" ] ; then
  echo "will try build with static libdb-4.6" 
  if ! [ -f "common/libdb-4.6.a" ]; then
    echo "missing file 'common/libdb-4.6.a' needed for static build"
    echo "build Berkelely DB 4.6 and find this in the following path"
    echo "build_unix/.libs/libdb-4.6.a"
    exit 1 
  fi
  static='static'
fi



rm -rf bin
mkdir bin 

cd common
make 
if [ $? -ne 0 ] ; then 
	echo "Error building in  'common'"
	exit 1
fi 

cd ../notary-server
if [ -f notary_server ] ; then
   rm notary_server
fi
  
make $static  
if [ $? -ne 0 ] ; then 
	echo "Error building in  'notary-server'"
	exit 1
fi 

cp notary_server ../bin/

cd ../notary-client
make
if [ $? -ne 0 ] ; then 
	echo "Error building in 'notary-client'"
	exit 1
fi


cd ../notary-http
if [ -f notary_http ] ; then
    rm notary_http
fi
make $static  
if [ $? -ne 0 ] ; then 
	echo "Error building in  'notary-http'"
	exit 1
fi 
cp notary_http ../bin/

cd ../key-scan
if [ -f notary_scanner ] ; then
    rm notary_scanner
fi
make $static  
if [ $? -ne 0 ] ; then 
	echo "Error building in  'key-scan'"
	exit 1
fi 
cp notary_scanner ../bin

cd ../ssh-scanner
./configure --without-zlib-version-check
if [ $? -ne 0 ] ; then 
	echo "Error configuring in 'ssh-scanner'"
	exit 1
fi
make
if [ $? -ne 0 ] ; then 
	echo "Error building in 'ssh-scanner'"
	exit 1
fi
cp ssh ../bin/ssh_scan

cd ../ssl-scanner
./config shared
if [ $? -ne 0 ] ; then 
	echo "Error configuring in 'ssl-scanner'"
	exit 1
fi
cd apps
make 
if [ $? -ne 0 ] ; then 
	echo "Error building in 'ssl-scanner'"
	exit 1
fi 
cp openssl ../../bin/ssl_scan
cd ..

cd ../utilities
make
if [ $? -ne 0 ] ; then 
	echo "Error building in 'utilities'"
	exit 1
fi 

for f in db2file file2db full_client db_search signature_util request_scan
do
	cp $f ../bin
done 

echo "Build Done.  ./bin should hold your files" 

