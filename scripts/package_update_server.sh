#!/bin/sh

if ! [ -d "bin" ]; then
  echo "error, no 'bin' dir. Need to invoke scripts/build_server.sh first!" 
  exit 1
fi

if ! [ -d "scripts" ]; then
 echo "error, no 'scripts' dir found"
 exit 1
fi


version=`cat SERVER_VERSION`
fname="notary_update_dist-$version.tar.gz" 

if [ -f $fname ]; then
  rm $fname
fi

cd ..

find notarycode -type d -print | egrep '\.svn' >> exclude

tar czfX notarycode/$fname exclude notarycode/bin notarycode/scripts notarycode/SERVER_VERSION 

rm exclude

