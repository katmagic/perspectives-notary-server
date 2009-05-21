#!/bin/sh

usage() { 
    echo "usage: scann-config-file log-dir <notary-dir> "
    exit 1
} 

if [ $# != 2 ] && [ $# != 3 ] ; then 
  usage
fi 

if [ $# = 3 ] ; then
  cd $3
fi

if ! [ -d "bin" ] ; then 
  echo "must be invoked from the top level of the notary package"
  exit 1
fi

if ! [ -d $2 ] ; then 
  mkdir $2
fi

time=`date +%s`



if ! [ -f $1 ] ; then 
    echo "sorry, config file '$1' doesn't exist"
    exit 1 
fi
db_env_fname=$(cat $1 | grep db_env_fname | awk -F "=" '{print $2}') 
db_fname=$(cat $1 | grep db_fname | awk -F "=" '{print $2}') 

if ! [ -d "$db_env_fname" ]; then
    echo "ERROR: cannot find DB environment dir '$db_env_fname'"
    exit 1
fi

if ! [ -f "$db_env_fname/$db_fname" ]; then
    echo "ERROR: cannot find DB file '$db_env_fname/$db_fname'"
    exit 1
fi
  
file=$2/notary_backup_$time.txt.bzip2

bin/db2file $db_env_fname $db_fname | bzip2 -z > $file 


