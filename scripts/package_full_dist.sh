#!/usr/local/bin/bash

if ! [ -d "bin" ]; then
  echo "need to invoke scripts/build_server.sh first!" 
  exit 1
fi

if ! [ -d "config" ]; then
  echo "warning, no 'config' dir found" 
fi

if ! [ -d "db_env" ]; then
  echo "warning, no 'db_env' dir found" 
fi

if ! [ -d "scripts" ]; then
 echo "warning, no 'scripts' dir found"
fi

if [ -f "notary_full_dist.tar.gz" ]; then
  rm notary_full_dist.tar.gz
fi

tar -czf notary_full_dist.tar.gz bin config scripts db_env/*.db

