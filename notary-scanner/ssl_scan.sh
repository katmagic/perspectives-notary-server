#!/bin/sh 

if [ $# != 2 ] 
then
	echo "usage: <service-id> <report-sock-name>"
	exit 1
fi

ssl_scan_python $1 bin/report-observation $2 
