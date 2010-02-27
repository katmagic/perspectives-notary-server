#!@bash_EXEC@

exec >&2

set -e -u || exit 1

if [ "$#" != 1 ] ; then
	echo "usage: <daemon-name>"
	exit 1
fi

. '@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_user

name="$1"
exe='@notary_bin_PATH@/@notary_bin_PREFIX@'"$name"
pid='@notary_run_PATH@/'"$name"'.pid'
log='@notary_log_PATH@/'"$name"'.log'

echo
echo "INFO: checking daemon '$name'"

if ! [ -f "$exe" ] ; then
	echo "ERROR: cannot find executable file '$exe'"
	exit 1
fi

if ! [ -d '@notary_run_PATH@' ] ; then
	echo "ERROR: cannot find run folder '@notary_run_PATH@'"
	exit 1
fi

if ! [ -d '@notary_log_PATH@' ] ; then
	echo "ERROR: cannot find log folder '@notary_log_PATH@'"
	exit 1
fi

if ! [ -f "$pid" ] ; then
	echo "ERROR: cannot find pid file '$pid'"
	exit 1
fi

id="$(cat "$pid")"

if ! [ -d "/proc/$id" ] ; then
	echo "WARNING: process seems dead"
	rm "$pid"
	exit 1
else
	echo "INFO: process seems alive"
fi

echo >>"$log"
echo "INFO: checked daemon '$name' at $(date)" >>"$log"
echo >>"$log"

exit 0