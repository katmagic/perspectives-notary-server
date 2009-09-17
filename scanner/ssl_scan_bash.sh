#!@bash_EXEC@

if [ $# != 3 ] ; then
	echo "usage: <service-id> <record-obs-binary> <report-sock-name>"
	exit 1
fi

if ! [ -x $2 ]; then
	echo "$2 is not a valid binary"
	exit 1
fi

dns_and_port=`echo $1 | cut -d"," -f1`

out=`openssl s_client -connect $dns_and_port </dev/null | openssl x509 -fingerprint -md5 -noout`

if [ $? -ne 0 ] ; then
	echo "Error fetching SSL cert"
	exit 1
fi

fp=`echo $out | cut -d"=" -f2 | tr '[A-F]' '[a-f]'`

echo $fp

dns_name=`echo $dns_and_port | cut -d":" -f1`
port=`echo $dns_and_port | cut -d":" -f2`

$2 $dns_name $port 2 ssl $fp $3

if [ $? -ne 0 ] ; then
	echo "Error reporting result to notary-scanner socket"
	exit 1
fi
