#!/usr/local/bin/bash


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

cd ../key-scan
make clean

cd ../ssh-scanner
make clean

cd ../ssl-scanner
make clean 

cd ../utilities
make clean 

cd ..

fname="notary_src_server.tar.gz"; 

if [ -f "$fname" ]; then
  rm $fname
fi

cd ..

find notarycode -type d -print | egrep '\.svn' >> exclude
echo "common/libdb-4.6.a" >> exclude

# note: we need to keep the notarycode/ in from of each name, otherwise 
#the exclude doesn't work!
tar czfX notarycode/$fname exclude notarycode/README notarycode/scripts notarycode/common notarycode/notary-server notarycode/notary-client notarycode/key-scan notarycode/ssh-scanner notarycode/ssl-scanner notarycode/utilities notarycode/config

rm exclude

echo "built: $fname" 
