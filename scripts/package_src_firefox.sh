#!/usr/local/bin/bash


if ! [ -d "firefox-plugin" ]; then
  echo "Error: Script must be run from top of notarycode directory"
  echo "EXITING"
  exit 1
fi

fname="notary_src_firefox.tar.gz"; 

if [ -f "$fname" ]; then
  rm $fname
fi

cd common
make clean  

cd ../notary-client
make clean

cd ../firefox-plugin
./make-plugin.sh clean 

cd ../..

find notarycode -type d -print | egrep '\.svn' >> exclude

tar czfX notarycode/$fname exclude notarycode/firefox-plugin notarycode/common notarycode/notary-client

rm exclude

echo "built: $fname" 
