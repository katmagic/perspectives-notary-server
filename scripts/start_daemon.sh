#!@bash_EXEC@

exec >&2

set -e -u || exit 1

if [ "$#" != 2 ] ; then
	echo "usage: <daemon-name> <daemon-config>"
	exit 1
fi

name="$1"
conf="$2"
exe='@notary_bin_PATH@/@notary_bin_PREFIX@'"$name"
pid='@notary_run_PATH@/'"$name"'.pid'
log='@notary_log_PATH@/'"$name"'.log'

echo
echo "INFO: starting daemon '$name' configured with '$conf'"

if ! [ -f "$exe" ] ; then
	echo "ERROR: cannot find executable file '$exe'"
	exit 1
fi

if ! [ -f "$conf" ] ; then
	echo "ERROR: cannot find config file '$conf'"
	exit 1
fi

if ! [ -d '@notary_run_PATH@' ] ; then
  echo "WARNING: cannot find run folder '@notary_run_PATH@'"
  mkdir -p '@notary_run_PATH@'
fi

if ! [ -d '@notary_log_PATH@' ] ; then
  echo "WARNING: cannot find log folder '@notary_log_PATH@'"
  mkdir -p '@notary_log_PATH@'
fi

if [ -f "$pid" ] ; then
	echo "ERROR: pid file '$pid' already exists"
	id="$(cat "$pid")"
	if [ -d "/proc/$id" ] ; then
		echo "ERROR: process seems alive"
		exit 1
	else
		echo "WARNING: process seems dead"
		rm "$pid"
	fi
fi

echo >>"$log"
echo "INFO: starting daemon '$name' configured with '$conf' at $(date)" >>"$log"
echo >>"$log"

"$exe" "$conf" </dev/null >>"$log" 2>&1 &
id="$!"

sleep 0.1s

if ! [ -d "/proc/$id" ] ; then
	echo "ERROR: process seems to have failed"
	echo >>"$log"
	echo "ERROR: process seems to have failed" >> "$log"
	echo >>"$log"
	exit 1
fi

echo "$id" >"$pid"

echo "INFO: started successfully"

exit 0
