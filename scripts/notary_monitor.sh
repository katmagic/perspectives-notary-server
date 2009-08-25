#!/bin/sh

if [ $# != 1 ]; then
	echo "usage: <http-server-config-file>" 
	exit 1
fi

# it would be nice to do an 'end-to-end' test that can tell if the
# notary is actually responding with real data.  Right now, we just
# check that a process is running, which won't catch DB corruption 
# issues.  
while [ true ]; do
	res=`ps -A | grep notary_http | grep -v grep`
	if [ ${#res} = 0 ]; then
		echo "restarted by monitor" >> log/http-server.log 
		./scripts/start_http_server.sh $1
	fi
	sleep 3
done
