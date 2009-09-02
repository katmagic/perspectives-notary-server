#!/bin/sh

usage() { 
    echo "usage: db <scann-config-file> <max-simultaneous> <timeout>"
    echo "usage: f <service-list-file> <max-simultaneous> <timeout>"
    exit 1
} 

if [ $# != 4 ] && [ $# != 5 ] ; then 
  usage
fi 

if [ $# = 5 ] ; then
  cd $5
fi

if ! [ -d "bin" ] ; then 
  echo "must be invoked from the top level of the notary package"
  exit 1
fi

if ! [ -d "log" ] ; then 
  mkdir log
fi

time=`date +%s`


if [ $1 = "db" ]; then

  if ! [ -f $2 ] ; then 
    echo "sorry, config file '$2' doesn't exist"
    exit 1 
  fi
  db_env_fname=$(cat $2 | grep db_env_fname | awk -F "=" '{print $2}') 
  db_fname=$(cat $2 | grep db_fname | awk -F "=" '{print $2}') 

  if ! [ -d "$db_env_fname" ]; then
    echo "ERROR: cannot find DB environment dir '$db_env_fname'"
    exit 1
  fi

  if ! [ -f "$db_env_fname/$db_fname" ]; then
    echo "ERROR: cannot find DB file '$db_env_fname/$db_fname'"
    exit 1
  fi
  
  file=log/scanned_hosts_$time.txt

  python scripts/list_by_last_obs.py $db_env_fname $db_fname older 0 | awk '{print $1}' > $file


elif [ "$1" = "f" ]; then
  if ! [ -f $2 ]; then
    echo "Error: couldn't locate input file '$2'"
    usage 
  fi 
  file=$2
else 
  usage 
fi

python scripts/simple_scanner.py $file $3 $4 $2 >> log/scan_results.log 2>&1

