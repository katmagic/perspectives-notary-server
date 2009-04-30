#!/bin/sh


if ! [ -d "firefox-v2" ]; then
  echo "Error: Script must be run from top of notarycode directory"
  echo "EXITING"
  exit 1
fi

fname="notary_src_firefox.tar.gz"; 

if [ -f "$fname" ]; then
  rm $fname
fi

cd ..

echo "notarycode/firefox-v3/Perspectives.xpi" >> exclude
find notarycode -type d -print | egrep '\.svn' >> exclude

tar czfX notarycode/$fname exclude notarycode/firefox-v3 notarycode/COPYING notarycode/config/http_notary_list.txt

rm exclude

echo "built: $fname" 
