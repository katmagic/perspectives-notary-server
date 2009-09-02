#!/bin/sh

if [ $# != 5 ] 
then 
  echo "usage: notary-address notary-port service-address port service-type"
  exit 1
fi

wget --output-document=- "http://$1:$2?host=$3&port=$4&service_type=$5"

