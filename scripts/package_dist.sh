#!/bin/sh

if ! [ -d "bin" ]; then
  echo "need to invoke scripts/build_server.sh first!" 
  exit 1
fi

if ! [ -d "scripts" ]; then
 echo "warning, no 'scripts' dir found"
fi

if [ -f "notary_dist.tar.gz" ]; then
  rm notary_dist.tar.gz
fi

tar -czf notary_dist.tar.gz bin scripts

