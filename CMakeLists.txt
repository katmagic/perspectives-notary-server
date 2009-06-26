
project (notary)

cmake_minimum_required (VERSION 2.6)

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


set (notary_common_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-common' library.")

set (notary_client_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-client' library.")

set (notary_client_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-client' executable.")

set (notary_scanner_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-scanner' executable.")

set (notary_ssl_scanner_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-ssl-scanner' executable.")

#set (notary_ssh_scanner_ENABLED
#		ON
#		CACHE BOOL "Enable building 'notary-ssh-scanner' executable.")

set (notary_http_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-http' executable.")

set (notary_server_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-server' executable.")

set (utilities_ENABLED
		ON
		CACHE BOOL "Enable building utilities executables.")

if (notary_common_ENABLED)
	add_subdirectory (notary-common)
else ()
	message ("Disabled building 'notary-common' library.")
endif ()

if (notary_common_ENABLED AND notary_client_ENABLED)
	add_subdirectory (notary-client)
else ()
	message ("Disabled building 'notary-client' library.")
endif ()

if (notary_common_ENABLED AND notary_scanner_ENABLED)
	add_subdirectory (notary-scanner)
else ()
	message ("Disabled building 'notary-scanner' executable.")
endif ()

if (notary_ssl_scanner_ENABLED)
	add_subdirectory (notary-ssl-scanner)
else ()
	message ("Disabled building 'notary-ssl-scanner' executable.")
endif ()

#if (notary_ssh_scanner_ENABLED)
#	add_subdirectory (notary-ssh-scanner)
#else ()
#	message ("Disabled building 'notary-ssh-scanner' executable.")
#endif ()

if (notary_common_ENABLED AND notary_client_ENABLED AND notary_http_ENABLED)
	add_subdirectory (notary-http)
else ()
	message ("Disabled building 'notary-http' executable.")
endif ()

if (notary_common_ENABLED AND notary_server_ENABLED)
	add_subdirectory (notary-server)
else ()
	message ("Disabled building 'notary-server' executable.")
endif ()

if (notary_common_ENABLED AND notary_client_ENABLED AND utilities_ENABLED)
	add_subdirectory (utilities)
else ()
	message ("Disabled building utilities executables.")
endif ()
