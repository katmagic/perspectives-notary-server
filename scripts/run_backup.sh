#!/bin/sh

exec >&2

if [ "$#" != 2 ] ; then
  echo "usage: <scanner-config> <backup-dir>"
  exit 1
fi

if ! [ -f $1 ] ; then
    echo "ERROR: cannot find config file '$1'"
    exit 1
fi

db_env_fname="$(cat "$1" | grep db_env_fname | awk -F = '{print $2}')"
db_fname="$(cat "$1" | grep db_fname | awk -F = '{print $2}')"

if ! [ -d "$db_env_fname" ] ; then
    echo "ERROR: cannot find DB environment dir '$db_env_fname'"
    exit 1
fi

if ! [ -f "$db_env_fname/$db_fname" ] ; then
    echo "ERROR: cannot find DB file '$db_env_fname/$db_fname'"
    exit 1
fi

time="$(date '+%Y-%m-%d-%H-%M-%S')"

if ! [ -d "$2" ] ; then
  echo "WARNING: cannot find backup dir '$2'"
  mkdir -p "$2"
fi

file="$2/notary_backup_$time.txt.bzip2"
echo "INFO: creating backup file '$file'"
'@notary_bin_PATH@/@notary_bin_PREFIX@'db2file "$db_env_fname" "$db_fname" | bzip2 -z > "$file"

exit 0
