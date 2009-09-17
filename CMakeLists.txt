
cmake_minimum_required (VERSION 2.6)


project (notary)

set (notary_VERSION_MAJOR 2)
set (notary_VERSION_MINOR 0)


find_path (bdb_INCLUDE_DIR db.h
		/usr/include /usr/local/include
		/opt/include /opt/local/include)

find_library (bdb_LIBRARIES db
		/lib
		/usr/lib /usr/local/lib
		/opt/lib /opt/local/lib)

find_path (openssl_INCLUDE_DIR openssl/ssl.h
		/usr/include /usr/local/include
		/opt/include /opt/local/include)

find_library (openssl_LIBRARIES ssl
		/lib
		/usr/lib /usr/local/lib
		/opt/lib /opt/local/lib)

find_path (crypto_INCLUDE_DIR openssl/crypto.h
		/usr/include /usr/local/include
		/opt/include /opt/local/include)

find_library (crypto_LIBRARIES crypto
		/lib
		/usr/lib /usr/local/lib
		/opt/lib /opt/local/lib)

set (additional_INCLUDE_DIR
		CACHE PATH "Additional folders for including.")

set (additional_LIBRARIES
		CACHE FILEPATH "Additional libraries for linking.")


set (notary_common_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-common' library.")

set (notary_http_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-http' executable.")

set (notary_scanner_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-scanner' executable.")

set (utilities_ENABLED
		ON
		CACHE BOOL "Enable building utility executables.")

set (configurations_ENABLED
		ON
		CACHE BOOL "Enable building configuration files.")

set (scripts_ENABLED
		ON
		CACHE BOOL "Enable building script files.")


set (CMAKE_INSTALL_PREFIX
		"/tmp/notary"
		CACHE PATH "Installation prefix" FORCE)

set (notary_MANGLING
		"notary-b"
		CACHE STRING "Text to prefix executables or to derive paths names.")

set (notary_bin_PREFIX
		"${notary_MANGLING}-"
		CACHE STRING "Prefix of the executable files.")

set (notary_bin_PATH
		"${CMAKE_INSTALL_PREFIX}/bin"
		CACHE PATH "Path of the executable files.")

set (notary_etc_PATH
		"${CMAKE_INSTALL_PREFIX}/etc/${notary_MANGLING}"
		CACHE PATH "Path of the configuration files.")

set (notary_var_PATH
		"${CMAKE_INSTALL_PREFIX}/var/${notary_MANGLING}"
		CACHE PATH "Path of the data files.")

set (notary_db_PATH
		"${notary_var_PATH}/db"
		CACHE PATH "Path of the BerkeleyDB environment.")

set (notary_db_NAME
		"notary.db"
		CACHE PATH "Name of the BerkeleyDB name.")

set (notary_sock_PATH
		"${notary_var_PATH}/sock"
		CACHE PATH "Path of the sockets.")

set (notary_private_key_PATH
		"${notary_etc_PATH}/private_key.pem"
		CACHE PATH "Path of the private key.")

set (notary_public_key_PATH
		"${notary_etc_PATH}/public_key.pem"
		CACHE PATH "Path of the public key.")

set (notary_http_listen_IP
		"0.0.0.0"
		CACHE STRING "Listening IP of the notary http server.")

set (notary_http_listen_PORT
		"8080"
		CACHE STRING "Listening port of the notary http server.")

set (notary_new_request_socket_PATH
		"${notary_sock_PATH}/new_request"
		CACHE PATH "Unix domain socket path for new requests.")

set (notary_finished_request_socket_PATH
		"${notary_sock_PATH}/finished_request"
		CACHE PATH "Unix domain socket path for finished requests.")


if (notary_common_ENABLED)
	add_subdirectory (notary-common)
else ()
	message ("Disabled building 'notary-common' library.")
endif ()

if (notary_common_ENABLED AND notary_http_ENABLED)
	add_subdirectory (notary-http)
else ()
	message ("Disabled building 'notary-http' executable.")
endif ()

if (notary_common_ENABLED AND notary_scanner_ENABLED)
	add_subdirectory (notary-scanner)
else ()
	message ("Disabled building 'notary-scanner' executable.")
endif ()

if (notary_common_ENABLED AND utilities_ENABLED)
	add_subdirectory (utilities)
else ()
	message ("Disabled building utility executables.")
endif ()

if (configurations_ENABLED)
	add_subdirectory (config)
else ()
	message ("Disabled building configuration files.")
endif ()

if (scripts_ENABLED)
	add_subdirectory (scripts)
else ()
	message ("Disabled building script files.")
endif ()
