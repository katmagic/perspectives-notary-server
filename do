#!/bin/bash

set -e -u -o pipefail || exit 1

# if no arguments are given, assume it is the 'help' command
test "${#}" -ge 1 || exec "${0}" help

# chdir to the root of the source tree
cd "$( dirname "${0}" )"
test -f ./do

case "${1}" in
	
	( help )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		version="$( cat ./VERSION )"
		sed -r -e "s|@VERSION@|${version}|g" <./README | less
		exit 0
	;;
	
	( license )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		exec less ./COPYING
	;;
	
	( clean )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		test -e ./build || { echo "already clean!" >&2 ; exit 0 ; }
		find ./build -delete || true
		exit 0
	;;
	
	( configure )
		shift
		test -e ./build || mkdir ./build
		cd ./build
		test "${#}" -eq 0 || exec cmake "${@}" ..
		exec cmake ..
	;;
	
	( configure-ui )
		shift
		test -e ./build || mkdir ./build
		cd ./build
		test "${#}" -eq 0 || exec ccmake "${@}" ..
		exec ccmake ..
	;;
	
	( make )
		shift
		test -e ./build || { echo "configure first!" >&2 ; exit 1 ; }
		cd ./build
		test "${#}" -eq 0 || exec make "${@}"
		exec make all
	;;
	
	( test-shell )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		./do configure -Dnotary_PATH=/tmp/notary -Dnotary_PATH_MANGLING= -Dnotary_static_ENABLED=off
		./do make
		./do make install
		cd /tmp/notary
		export PATH="/tmp/notary/bin:/tmp/notary/libexec:$PATH"
		export HISTFILE="/tmp/notary/.bash_history"
		export PS1='\nnotary> '
		cd /tmp/notary
		exec /bin/bash --noprofile --norc
	;;
	
	( test-clean )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		find ./build -delete || true
		find /tmp/notary -delete || true
		exit 0
	;;
	
	( * )
		echo "wrong command! try help!" >&2
		exit 1
	;;
esac

exit 1
