#!/bin/sh

set -e -u || exit 1

test -n "${INSIDE_BASH:-}" || exec env INSIDE_BASH=x bash "${0}" "${@}" || exit 1

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
		exit 1
	;;
	
	( clean )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		test -e ./build || { echo "already clean!" >&2 ; exit 0 ; }
		find ./build -delete || true
		exit 0
	;;
	
	( dependencies )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		test -z "${cmake_PREFIX:-}" || export PATH="${cmake_PREFIX}/bin:${PATH}"
		test -z "${bdb_PREFIX:-}" || export PATH="${bdb_PREFIX}/bin:${PATH}"
		test -z "${openssl_PREFIX:-}" || export PATH="${openssl_PREFIX}/bin:${PATH}"
		bash="$( bash --version 2>&1 | head -n 1 | grep -o -E -e '[0-9][0-9a-zA-Z_.+()-]+' | head -n 1 )"
		python="$( python -V 2>&1 | head -n 1 | grep -o -E -e '[0-9][0-9a-zA-Z_.+()-]+' | head -n 1 )"
		cmake="$( "${cmake_EXEC:-cmake}" --version 2>&1 | head -n 1 | grep -o -E -e '[0-9][0-9a-zA-Z_.+()-]+' | head -n 1 )"
		make="$( make --version 2>&1 | head -n 1 | grep -o -E -e '[0-9][0-9a-zA-Z_.+()-]+' | head -n 1 )"
		gcc="$( gcc --version 2>&1 | head -n 1 | grep -o -E -e '[0-9][0-9a-zA-Z_.+()-]+' | head -n 1 )"
		bdb="$( for verify in db{,4{.{8..0},}}_verify ; do "${verify}" -V 2>&1 && break ; done | head -n 1 | grep -o -E -e '[0-9][0-9a-zA-Z_.+()-]+' | head -n 1 )"
		openssl="$( openssl version 2>&1 | head -n 1 | grep -o -E -e '[0-9][0-9a-zA-Z_.+()-]+' | head -n 1 )"
		openssh="$( ssh -V 2>&1 | head -n 1 | grep -o -E -e '[0-9][0-9a-zA-Z_.+()-]+' | head -n 1 )"
		echo "OS:         ${OSTYPE:-unknown!!!!}" >&2
		echo "Bash:       ${bash:-missing!!!!} $( which bash )" >&2
		echo "Python:     ${python:-missing!!!!} $( which python )" >&2
		echo "CMake:      ${cmake:-missing!!!!} $( which cmake )" >&2
		echo "Make:       ${make:-missing!!!!} $( which make )" >&2
		echo "GCC:        ${gcc:-missing!!!!} $( which gcc )" >&2
		echo "BerkeleyDB: ${bdb:-missing!!!!} $( which db_verify )" >&2
		echo "OpenSSL:    ${openssl:-missing!!!!} $( which openssl )" >&2
		echo "OpenSSH:    ${openssh:-missing!!!!} $( which ssh )" >&2
		case "1${OSTYPE:-unknown}" in
			( linux-* | freebsd )
			;;
			( * )
				echo "!!!! This OS was not tested. !!!!" >&2
			;;
		esac
		echo "(note: this is only informative!)" >&2
		exit 0
	;;
	
	( configure )
		shift
		test -z "${cmake_PREFIX:-}" || export PATH="${cmake_PREFIX}/bin:${PATH}"
		cmake="${cmake_EXEC:-$( which cmake )}"
		test -n "${cmake}" || { echo "cmake not found!" >&2 ; exit 1 ; }
		test -e ./build || mkdir ./build
		cd ./build
		test "${#}" -eq 0 || exec "${cmake}" "${@}" ..
		exec "${cmake}" ..
		exit 1
	;;
	
	( configure-ui )
		shift
		test -z "${cmake_PREFIX:-}" || export PATH="${cmake_PREFIX}/bin:${PATH}"
		ccmake="${ccmake_EXEC:-$( which ccmake )}"
		test -n "${ccmake}" || { echo "cmake not found!" >&2 ; exit 1 ; }
		test -e ./build || mkdir ./build
		cd ./build
		test "${#}" -eq 0 || exec "${ccmake}" "${@}" ..
		exec "${ccmake}" ..
		exit 1
	;;
	
	( make )
		shift
		make="${make_EXEC:-$( which make )}"
		test -n "${make}" || { echo "make not found!" >&2 ; exit 1 ; }
		test -e ./build || { echo "build directory not found! configure first!" >&2 ; exit 1 ; }
		cd ./build
		test "${#}" -eq 0 || exec "${make}" "${@}"
		exec "${make}" all
		exit 1
	;;
	
	( test-shell )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		deployment="/tmp/notary.${USER}"
		./do configure -Dnotary_PATH="${deployment}" -Dnotary_PATH_MANGLING= -Dnotary_static_ENABLED=off
		./do make
		./do make install
		cd "${deployment}"
		export PATH="${deployment}/bin:${deployment}/libexec:${PATH}"
		export HISTFILE="${deployment}/.bash_history"
		export PS1='\nnotary> '
		cd "${deployment}"
		exec bash --noprofile --norc
		exit 1
	;;
	
	( test-clean )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		deployment="/tmp/notary.${USER}"
		./do clean
		test -e "${deployment}" || { echo "already clean!" >&2 ; exit 0 ; }
		find "${deployment}" -delete || true
		exit 0
	;;
	
	( cmake-install )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		version="${cmake_install__version:-2.8.0}"
		destination="${cmake_install__destination:-${HOME}/.packages/cmake/${version}}"
		temporary="${cmake_temporary__temporary:-/tmp/notary.cmake.build.${USER}/${version}}"
		bundle_url="${cmake_install__bundle_url:-http://www.cmake.org/files/v2.8/cmake-${version}.tar.gz}"
		bundle_path="${temporary}/cmake-${version}.tar.gz"
		echo "* CMake will be installed in ${destination}" >&2
		echo "* using ${temporary} as temporary folder" >&2
		echo "* downloading from ${bundle_url}" >&2
		echo >&2
		echo >&2
		test ! -e "${destination}" || { echo "CMake seems already installed!" >&2 ; exit 1 ; }
		test -e "${temporary}" || mkdir -p "${temporary}"
		test -e "${bundle_path}" || wget -O "${bundle_path}" "${bundle_url}"
		test -e "${temporary}/cmake-${version}" || rm -R -f "${temporary}/cmake-${version}"
		tar -xzf "${bundle_path}" -C "${temporary}"
		pushd "${temporary}/cmake-${version}" >/dev/null
		./configure --prefix="${destination}"
		make
		test -e "${destination}" || mkdir -p "${destination}"
		make install
		popd >/dev/null
		echo >&2
		echo >&2
		echo "CMake installation succeeded!" >&2
		echo "Now in the shell:" >&2
		echo ">> export cmake_PREFIX='${destination}'" >&2
		rm -R -f "${temporary}"
		exit 0
	;;
	
	( bdb-install )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		version="${bdb_install__version:-4.8.24}"
		destination="${bdb_install__destination:-${HOME}/.packages/bdb/${version}}"
		temporary="${bdb_temporary__temporary:-/tmp/notary.bdb.build.${USER}/${version}}"
		bundle_url="${bdb_install__bundle_url:-http://download.oracle.com/berkeley-db/db-${version}.tar.gz}"
		bundle_path="${temporary}/bdb-${version}.tar.gz"
		echo "* BerkeleyDB will be installed in ${destination}" >&2
		echo "* using ${temporary} as temporary folder" >&2
		echo "* downloading from ${bundle_url}" >&2
		echo >&2
		echo >&2
		test ! -e "${destination}" || { echo "OpenSSL seems already installed!" >&2 ; exit 1 ; }
		test -e "${temporary}" || mkdir -p "${temporary}"
		test -e "${bundle_path}" || wget -O "${bundle_path}" "${bundle_url}"
		test -e "${temporary}/bdb-${version}" || rm -R -f "${temporary}/bdb-${version}"
		tar -xzf "${bundle_path}" -C "${temporary}"
		pushd "${temporary}/db-${version}/build_unix" >/dev/null
		../dist/configure --prefix="${destination}" --enable-static --enable-shared
		make
		test -e "${destination}" || mkdir -p "${destination}"
		make install
		popd >/dev/null
		echo >&2
		echo >&2
		echo "OpenSSL installation succeeded!" >&2
		echo "Now in the shell:" >&2
		echo ">> export bdb_PREFIX='${destination}'" >&2
		rm -R -f "${temporary}"
		exit 0
	;;
	
	( openssl-install )
		shift
		test "${#}" -eq 0 || { echo "wrong arguments! try help!" >&2 ; exit 1 ; }
		version="${openssl_install__version:-0.9.8l}"
		destination="${openssl_install__destination:-${HOME}/.packages/openssl/${version}}"
		temporary="${openssl_temporary__temporary:-/tmp/notary.openssl.build.${USER}/${version}}"
		bundle_url="${openssl_install__bundle_url:-http://www.openssl.org/source/openssl-${version}.tar.gz}"
		bundle_path="${temporary}/openssl-${version}.tar.gz"
		echo "* OpenSSL will be installed in ${destination}" >&2
		echo "* using ${temporary} as temporary folder" >&2
		echo "* downloading from ${bundle_url}" >&2
		echo >&2
		echo >&2
		test ! -e "${destination}" || { echo "OpenSSL seems already installed!" >&2 ; exit 1 ; }
		test -e "${temporary}" || mkdir -p "${temporary}"
		test -e "${bundle_path}" || wget -O "${bundle_path}" "${bundle_url}"
		test -e "${temporary}/openssl-${version}" || rm -R -f "${temporary}/openssl-${version}"
		tar -xzf "${bundle_path}" -C "${temporary}"
		pushd "${temporary}/openssl-${version}" >/dev/null
		./config --prefix="${destination}" shared
		make
		test -e "${destination}" || mkdir -p "${destination}"
		make install
		popd >/dev/null
		echo >&2
		echo >&2
		echo "OpenSSL installation succeeded!" >&2
		echo "Now in the shell:" >&2
		echo ">> export openssl_PREFIX='${destination}'" >&2
		rm -R -f "${temporary}"
		exit 0
	;;
	
	( * )
		echo "wrong command! try help!" >&2
		exit 1
	;;
esac

exit 1
