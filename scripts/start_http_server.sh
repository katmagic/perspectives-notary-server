#!@bash_EXEC@

exec >&2

if [ "$#" != 1 ] ; then
  echo "usage: <http-server-config>"
  exit 1
fi

if ! [ -f "$1" ] ; then
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

if ! [ -d '@notary_run_PATH@' ] ; then
  echo "WARNING: cannot find run dir '@notary_run_PATH@'"
  mkdir -p '@notary_run_PATH@'
fi

if ! [ -d '@notary_log_PATH@' ] ; then
  echo "WARNING: cannot find log dir '@notary_log_PATH@'"
  mkdir -p '@notary_log_PATH@'
fi

pid_fname='@notary_run_PATH@'/http_server.pid

if [ -f "$pid_fname" ] ; then
  echo "ERROR: pid file '$pid_fname' already exists; please kill"
  exit 1
fi

echo "INFO: starting http_server"
echo >> '@notary_log_PATH@'/http_server.log
echo "INFO: starting http_server at $(date)" >> '@notary_log_PATH@'/http_server.log

'@notary_bin_PATH@/@notary_bin_PREFIX@'http_server "$1" >> '@notary_log_PATH@'/http_server.log 2>&1 &
echo "$!" > "$pid_fname"

exit 0
