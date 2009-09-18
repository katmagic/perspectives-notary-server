#!@bash_EXEC@

exec >&2

usage() {
  echo "usage: db <scanner-config> <max-simultaneous> <timeout>"
  echo "usage: f <service-list> <max-simultaneous> <timeout>"
  exit 1
}

if [ "$#" != 4 ] ; then
  usage
fi

echo
echo "INFO: scanning"

if ! [ -d '@notary_run_PATH@' ] ; then
  echo "WARNING: cannot find run dir '@notary_run_PATH@'"
  mkdir -p '@notary_run_PATH@'
fi

if ! [ -d '@notary_log_PATH@' ] ; then
  echo "WARNING: cannot find log dir '@notary_log_PATH@'"
  mkdir -p '@notary_log_PATH@'
fi

time="$(date '+%Y-%m-%d-%H-%M-%S')"

if [ "$1" = db ] ; then

  if ! [ -f "$2" ] ; then
    echo "ERROR: cannot find config file '$2'"
    exit 1
  fi

  db_env_fname="$(cat "$2" | grep db_env_fname | awk -F = '{print $2}')"
  db_fname="$(cat "$2" | grep db_fname | awk -F = '{print $2}')"

  if ! [ -d "$db_env_fname" ] ; then
    echo "ERROR: cannot find DB environment dir '$db_env_fname'"
    exit 1
  fi

  if ! [ -f "$db_env_fname/$db_fname" ] ; then
    echo "ERROR: cannot find DB file '$db_env_fname/$db_fname'"
    exit 1
  fi

  file='@notary_run_PATH@'/"scan_$time.in"
  echo "INFO: dumping db"
  '@notary_bin_PATH@/@notary_bin_PREFIX@'list_by_last_obs "$db_env_fname" "$db_fname" older 0 | awk '{print $1}' > "$file"

elif [ "$1" = f ] ; then

  if ! [ -f "$2" ]; then
    echo "ERROR: cannot find input file '$2'"
  fi

  file="$2"

else
  usage
fi

echo "" >> '@notary_log_PATH@'/scan.log
echo "INFO: starting db_manager at $(date)" >> '@notary_log_PATH@'/scan.log
echo "" >> '@notary_log_PATH@'/scan.log
'@notary_bin_PATH@/@notary_bin_PREFIX@'simple_scanner "$file" "$3" "$4" "$2" 2>&1 | tee -a '@notary_log_PATH@'/scan.log

if [ "$1" = db ] ; then
  echo "INFO: cleaning"
  rm "$file"
fi

exit 0
