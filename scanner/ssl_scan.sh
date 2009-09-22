#!@bash_EXEC@

if [ "$#" != 2 ]
then
	echo "usage: <service-id> <report-sock-name>"
	exit 1
fi

exec '@notary_libexec_PATH@/@notary_libexec_PREFIX@'ssl_scan_python "$1" '@notary_libexec_PATH@/@notary_libexec_PREFIX@'report_observation "$2"

exit 1
