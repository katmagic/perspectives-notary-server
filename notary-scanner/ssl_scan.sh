#!@bash_EXEC@

if [ "$#" != 2 ]
then
	echo "usage: <service-id> <report-sock-name>"
	exit 1
fi

exec '@notary_bin_PATH@/@notary_bin_PREFIX@'ssl_scan_python "$1" '@notary_bin_PATH@/@notary_bin_PREFIX@'report-observation "$2"

exit 1
