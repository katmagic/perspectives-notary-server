#!/usr/local/bin/bash


if ! [ -d "firefox-v2" ]; then
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

cd ../firefox-v2/xp_src
make clean 

cd ../../..

echo "notarycode/firefox-v2/Perspectives.xpi" >> exclude
echo "notarycode/firefox-v2/ff_with_log.sh" >> exclude
echo "notarycode/firefox-v2/xulrunner-sdk" >> exclude
echo "notarycode/firefox-v2/build" >> exclude
#echo "notarycode/firefox-v2/dist" >> exclude
find notarycode -type d -print | egrep '\.svn' >> exclude

tar czfX notarycode/$fname exclude notarycode/firefox-v2 notarycode/common notarycode/notary-client notarycode/COPYING notarycode/README notarycode/config/notary_list.txt

rm exclude

echo "built: $fname" 
