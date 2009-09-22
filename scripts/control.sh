#!@bash_EXEC@

exec >&2

set -e -u -o pipefail || exit 1

usage () {
	echo "usage: start | stop | restart | check | maintenance"
	exit 1
}

if [ "$#" != 1 ] ; then
	usage
fi

case "${1}" in
	
	( start )
		@notary_bin_PATH@/@notary_bin_PREFIX@prime_db
		@notary_bin_PATH@/@notary_bin_PREFIX@start_daemons
		exit 0
	;;
	
	( stop )
		@notary_bin_PATH@/@notary_bin_PREFIX@stop_daemons
		@notary_bin_PATH@/@notary_bin_PREFIX@prime_db
		exit 0
	;;
	
	( restart )
		@notary_bin_PATH@/@notary_bin_PREFIX@stop_daemons
		@notary_bin_PATH@/@notary_bin_PREFIX@prime_db
		@notary_bin_PATH@/@notary_bin_PREFIX@start_daemons
	;;
	
	( check )
		exec @notary_bin_PATH@/@notary_bin_PREFIX@check_daemons
	;;
	
	( maintenance )
		exec @notary_bin_PATH@/@notary_bin_PREFIX@maintenance
	;;
	
	( * )
		usage
	;;
esac

exit 1
