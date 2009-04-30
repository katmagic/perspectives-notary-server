#!/bin/sh

if [ $# != 2 ]; then
  echo "usage: priv-key-out pub-key-out"
  exit 1
fi

len=1369

openssl genrsa -out $1 $len

openssl rsa -in $1 -out $2 -outform PEM -pubout

echo " create $len bit public ($2) private ($1) key-pair " 

