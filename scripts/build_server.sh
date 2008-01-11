#!/usr/local/bin/bash


if ! [ -d "notary-server" ]; then
  echo "Error: Script must be run from top of notarycode directory"
  echo "EXITING"
  exit 1
fi

static=0 

if [ $# = 1 ] && [ "$1" = "static" ] ; then
  echo "will try build with static libdb-4.6" 
  if ! [ -f "common/libdb-4.6.a" ]; then
    echo "missing file 'common/libdb-4.6.a' needed for static build"
    echo "build Berkelely DB 4.6 and find this in the following path"
    echo "build_unix/.libs/libdb-4.6.a"
    exit 1 
  fi
  static=1
fi



rm -rf bin
mkdir bin 

cd common
make 

cd ../notary-server
if [ $static == 1 ]; then
  if [ -f notary_server ] ; then
    rm notary_server
  fi
  make static
else
  make 
fi
cp notary_server ../bin/

cd ../key-scan
if [ $static == 1 ]; then
  if [ -f notary_scanner ] ; then
    rm notary_scanner
  fi
  make static
else
  make 
fi
cp notary_scanner ../bin

cd ../ssh-scanner
if ! [ -f "Makefile" ]; then
./configure
fi
make
cp ssh ../bin/ssh_scan

cd ../ssl-scanner
make
cp apps/openssl ../bin/ssl_scan

cd ../notary-client
make

cd ../utilities
make 
cp db2file ../bin
cp file2db ../bin 
cp full_client ../bin
cp db_search ../bin
cp signature_util ../bin
cp request_scan ../bin

echo "Build Done.  ./bin should hold your files" 

