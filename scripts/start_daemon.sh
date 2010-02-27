#!@bash_EXEC@

exec >&2

set -e -u || exit 1

if [ "$#" != 2 ] ; then
	echo "ERROR: usage: <daemon-name> <daemon-config>" >&2
	exit 1
fi

. '@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_user

name="$1"
conf="$2"
exe='@notary_bin_PATH@/@notary_bin_PREFIX@'"$name"
pid='@notary_run_PATH@/'"$name"'.pid'
log='@notary_log_PATH@/'"$name"'.log'

echo >&2
echo "INFO: starting daemon '$name' configured with '$conf'" >&2

if ! [ -f "$exe" ] ; then
	echo "ERROR: cannot find executable file '$exe'" >&2
	exit 1
fi

if ! [ -f "$conf" ] ; then
	echo "ERROR: cannot find config file '$conf'" >&2
	exit 1
fi

if ! [ -d '@notary_run_PATH@' ] ; then
  echo "WARNING: cannot find run folder '@notary_run_PATH@'" >&2
  mkdir -p '@notary_run_PATH@'
fi

if ! [ -d '@notary_log_PATH@' ] ; then
  echo "WARNING: cannot find log folder '@notary_log_PATH@'" >&2
  mkdir -p '@notary_log_PATH@'
fi

if [ -f "$pid" ] ; then
	echo "ERROR: pid file '$pid' already exists" >&2
	id="$(cat "$pid")"
	if [ -d "/proc/$id" ] ; then
		echo "ERROR: process seems alive" >&2
		exit 1
	else
		echo "WARNING: process seems dead" >&2
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
	echo "ERROR: process seems to have failed" >&2
	echo >>"$log"
	echo "ERROR: process seems to have failed" >> "$log"
	echo >>"$log"
	exit 1
fi

echo "$id" >"$pid"

echo "INFO: started successfully" >&2

exit 0
