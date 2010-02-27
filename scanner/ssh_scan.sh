#!@bash_EXEC@

exec < /dev/null > /dev/null

if ! [ "$#" == 2 ] ; then
	echo "ERROR: usage: <service-id> <report-sock-name>" >&2
	exit 1
fi

exec '@notary_libexec_PATH@/@notary_libexec_PREFIX@'ssh_scan_bash "$1" '@notary_libexec_PATH@/@notary_libexec_PREFIX@'report_observation "$2"
#exec '@notary_libexec_PATH@/@notary_libexec_PREFIX@'ssh_scan_python "$1" '@notary_libexec_PATH@/@notary_libexec_PREFIX@'report_observation "$2"

exit 1
