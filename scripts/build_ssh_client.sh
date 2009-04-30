#!/bin/sh


if ! [ -d "common" ]; then
  echo "Error: Script must be run from top of notarycode directory"
  echo "EXITING"
  exit 1
fi


if ! [ -d "bin" ]; then
  mkdir bin 
fi

if [ -f "bin/ssh" ]; then
 rm bin/ssh
fi

cd common
make 



cd ../notary-client
make

cd ../openssh-4.4p1
if ! [ -f "Makefile" ]; then
./configure --without-zlib-check 
fi
make
cp ssh ../bin/ssh

echo "Build Done.  ./bin should hold your files" 

