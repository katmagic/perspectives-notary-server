#!/bin/sh

if ! test -e run/notary-http.pid ; then
	echo "run/notary-http.pid does not exist.  Please kill manually"
	exit 1
fi

kill `cat run/notary-http.pid`

rm run/notary-http.pid 


