#!/bin/sh

f=notary-db-manager.pid

if ! test -e run/$f ; then
	echo "run/$f does not exist.  Please kill manually"
	exit 1
fi

kill `cat run/$f`

rm run/$f

