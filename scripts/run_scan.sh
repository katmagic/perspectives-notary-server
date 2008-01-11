#!/usr/local/bin/bash


function usage {

    echo "usage: db <scann-config-file>"
    echo "usage: f <service-list-file>"
    exit 1
}

if [ $# != 2 ] && [ $# != 3 ] ; then 
  usage;  
fi 

if [ $# = 3 ] ; then
  cd $3
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

  bin/db2file $db_env_fname $db_fname | grep "Start Host" | awk -F "'" '{print $2}' > log/scan_list_$time.txt

  file=log/scan_list_$time.txt

elif [ "$1" = "f" ]; then
  if ! [ -f $2 ]; then
    echo "Error: couldn't locate input file '$2'"
    usage; 
  fi 
  file=$2
else 
  usage; 
fi

./bin/request_scan $file > log/scan_requests.log 2>&1

