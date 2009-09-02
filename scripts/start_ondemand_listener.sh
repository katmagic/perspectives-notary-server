#!/bin/sh

if [ $# != 1 ] 
then 
  echo "usage: <scanner-config>"
  exit 1
fi

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

if ! [ -d "log" ] ; then 
  mkdir log
fi

ulimit -c unlimited

echo " Restarting ondemand_listener at: `date` " >> log/on-demand.log
python scripts/notary_ondemand_listener.py $1 >> log/on-demand.log 2>&1 &

echo $! > run/notary_ondemand_listener.pid
