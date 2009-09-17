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
		exec find ./build -delete
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
		exec make
	;;
	
	( * )
		echo "wrong command! try help!" >&2
		exit 1
	;;
esac

exit 1
