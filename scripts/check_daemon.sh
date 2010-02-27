#!@bash_EXEC@

exec >&2

set -e -u || exit 1

if [ "$#" != 1 ] ; then
	echo "ERROR: usage: <daemon-name>" >&2
	exit 1
fi

. '@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_user

name="$1"
exe='@notary_bin_PATH@/@notary_bin_PREFIX@'"$name"
pid='@notary_run_PATH@/'"$name"'.pid'
log='@notary_log_PATH@/'"$name"'.log'

echo >&2
echo "INFO: checking daemon '$name'" >&2

if ! [ -f "$exe" ] ; then
	echo "ERROR: cannot find executable file '$exe'" >&2
	exit 1
fi

if ! [ -d '@notary_run_PATH@' ] ; then
	echo "ERROR: cannot find run folder '@notary_run_PATH@'" >&2
	exit 1
fi

if ! [ -d '@notary_log_PATH@' ] ; then
	echo "ERROR: cannot find log folder '@notary_log_PATH@'" >&2
	exit 1
fi

if ! [ -f "$pid" ] ; then
	echo "ERROR: cannot find pid file '$pid'" >&2
	exit 1
fi

id="$(cat "$pid")"

if ! [ -d "/proc/$id" ] ; then
	echo "WARNING: process seems dead" >&2
	rm "$pid"
	exit 1
else
	echo "INFO: process seems alive" >&2
fi

echo >>"$log"
echo "INFO: checked daemon '$name' at $(date)" >>"$log"
echo >>"$log"

exit 0
