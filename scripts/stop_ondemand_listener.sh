#!/bin/sh

if ! test -e run/notary_ondemand_listener.pid ; then
	echo "run/notary_ondemand_listener.pid does not exist.  Please kill manually"
	exit 1
fi

kill `cat run/notary_ondemand_listener.pid`

rm run/notary_ondemand_listener.pid 

