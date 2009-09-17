#!@bash_EXEC@

exec >&2

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

exec tail -f '@notary_log_PATH@'/*.log

exit 0
