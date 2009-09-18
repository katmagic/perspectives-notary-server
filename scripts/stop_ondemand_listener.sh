#!@bash_EXEC@

exec >&2

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

pid_fname='@notary_run_PATH@'/ondemand_listener.pid

if ! [ -f "$pid_fname" ] ; then
  echo "ERROR: cannot find pid file '$pid_fname'"
  exit 1
fi

echo "INFO: stopping ondemand_listener"

kill "$(cat "$pid_fname")"
rm "$pid_fname"

exit 0
