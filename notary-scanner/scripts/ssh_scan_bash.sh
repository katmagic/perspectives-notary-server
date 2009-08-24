#!/bin/sh

if [ $# != 2 ] ; then
	echo "usage: <service-id> <record-obs-binary>" 
	exit 1
fi

if ! [ -x $2 ]; then 
	echo "$2 is not a valid binary"
	exit 1
fi

dns_and_port=`echo $1 | cut -d"," -f1`
dns_name=`echo $dns_and_port | cut -d":" -f1`
port=`echo $dns_and_port | cut -d":" -f2`

key_file=`mktemp`
out=`ssh-keyscan -p $port $dns_name > "$key_file" && ssh-keygen -l -f "$key_file"`

if [ $? -ne 0 ] ; then 
	echo "Error fetching SSH cert"
	exit 1
fi
 

fp=`echo $out | cut -d" " -f2`

echo "fp='$fp'"

if ! [[ $fp =~ ".*" ]]
#if [[ "$fp" =~ '[a-f0-9]{2}(Z([a-f0-9]){2}){15}' ]]
then 
	echo "bad fingerprint '$fp'"
	exit 1
fi

$2 $dns_name $port 2 ssh $fp

if [ $? -ne 0 ] ; then 
	echo "Error reporting result to notary-scanner socket"
	exit 1
fi 

