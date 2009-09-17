#!/bin/bash

set -e -u -o pipefail || exit 1

# if no arguments are given, assume it is the 'help' command
test "${#}" -ge 1 || exec "${0}" help

# if more arguments are given, assume each one is an individual command and chain them
test "${#}" -eq 1 || { "${0}" "${1}" ; shift 1 ; exec "${0}" "${@}" ; }

# chdir to the root of the source tree
cd "$( dirname "${0}" )"
test -f ./do

case "${1}" in
	
	( help )
		version="$( cat ./VERSION )"
		sed -r -e "s|@VERSION@|${version}|g" <./README | less
		exit 0
	;;
	
	( license )
		exec less ./COPYING
	;;
	
	( clean )
		test -e ./build || { echo "already clean!" >&2 ; exit 0 ; }
		exec find ./build -delete
	;;
	
	( configure-auto )
		test -e ./build || mkdir ./build
		cd ./build
		exec cmake ..
	;;
	
	( configure-ui )
		test -e ./build || mkdir ./build
		cd ./build
		exec ccmake ..
	;;
	
	( build )
		test -e ./build || { echo "configure first!" >&2 ; exit 1 ; }
		cd ./build
		exec make
	;;
	
	( install )
		test -e ./build || { echo "configure first!" >&2 ; exit 1 ; }
		cd ./build
		exec make install
	;;
	
	( * )
		echo "wrong command! try help!" >&2
		exit 1
	;;
esac

exit 1
