#!/bin/sh


if ! [ -d "firefox-v3" ]; then
  echo "Error: Script must be run from top of notarycode directory"
  echo "EXITING"
  exit 1
fi

version=`head -n 1 FIREFOX_VERSION`
fname="notary_src_firefox-$version.tar.gz"; 

if [ -f "$fname" ]; then
  rm $fname
fi

cd ..

for f in Perspectives.xpi genupdate.sh mexumgen.pl update.rdf update_howto.txt; do 
	echo "notarycode/firefox-v3/$f" >> exclude
done
find notarycode -type d -print | egrep '\.svn' >> exclude

tar czfX notarycode/$fname exclude notarycode/firefox-v3 notarycode/COPYING notarycode/config/http_notary_list.txt notarycode/FIREFOX_README

rm exclude

echo "built: $fname" 
