#!/bin/bash

set -e -u -o pipefail || exit 1

# if no arguments are given, assume it is the 'build' command
test "${#}" -ge 1 || exec "${0}" build

# if more arguments are given, assume each one is an individual command and chain them
test "${#}" -eq 1 || { "${0}" "${1}" ; shift 1 ; exec "${0}" "${@}" ; }

case "${1}" in
	
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
		echo "wrong command!" >&2
		exit 1
	;;
esac

exit 1
