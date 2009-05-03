#!/bin/sh


if ! [ -d "notary-server" ]; then
  echo "Error: Script must be run from top of notarycode directory"
  echo "EXITING"
  exit 1
fi


cd common
make clean  

cd ../notary-client
make clean

cd ../notary-server
make clean  

cd ../notary-http
make clean  

cd ../key-scan
make clean

cd ../ssh-scanner
make clean

cd ../ssl-scanner
make clean 

cd ../utilities
make clean 

cd ..

version=`head -n 1 SERVER_VERSION`
fname="notary_src_server-$version.tar.gz"; 

if [ -f "$fname" ]; then
  rm $fname
fi

cd ..

find notarycode -type d -print | egrep '\.svn' >> exclude
echo "common/libdb-4.6.a" >> exclude

# note: we need to keep the notarycode/ in from of each name, otherwise 
#the exclude doesn't work!
tar czfX notarycode/$fname exclude notarycode/SERVER_VERSION notarycode/scripts notarycode/common notarycode/notary-server notarycode/notary-http notarycode/notary-client notarycode/key-scan notarycode/ssh-scanner notarycode/ssl-scanner notarycode/utilities notarycode/config

rm exclude

echo "built: $fname" 
