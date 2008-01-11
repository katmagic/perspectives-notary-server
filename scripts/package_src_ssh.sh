#!/usr/local/bin/bash


if ! [ -d "notary-client" ]; then
  echo "Error: Script must be run from top of notarycode directory"
  echo "EXITING"
  exit 1
fi


cd common
make clean  

cd ../notary-client
make clean

cd ../openssh-4.4p1
make clean 
rm Makefile

cd ..

fname="notary_src_ssh.tar.gz"; 

if [ -f "$fname" ]; then
  rm $fname
fi

cd ..

find notarycode -type d -print | egrep '\.svn' >> exclude
echo "notarycode/common/libdb-4.6.a" >> exclude

# note: we need to keep the notarycode/ in front of each name, 
#otherwise the exclude doesn't work!

tar czfX notarycode/$fname exclude notarycode/README notarycode/scripts notarycode/common notarycode/notary-client notarycode/openssh-4.4p1

rm exclude

echo "built: $fname" 
