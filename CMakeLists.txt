
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

set (notary_client_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-client' library.")

set (notary_scanner_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-scanner' executable.")

set (notary_http_ENABLED
		ON
		CACHE BOOL "Enable building 'notary-http' executable.")

set (utilities_ENABLED
		ON
		CACHE BOOL "Enable building utilities executables.")

if (notary_common_ENABLED)
	add_subdirectory (notary-common)
else ()
	message ("Disabled building 'notary-common' library.")
endif ()

if (notary_common_ENABLED AND notary_scanner_ENABLED)
	add_subdirectory (notary-scanner)
else ()
	message ("Disabled building 'notary-scanner' executable.")
endif ()


if (notary_common_ENABLED AND notary_http_ENABLED)
	add_subdirectory (notary-http)
else ()
	message ("Disabled building 'notary-http' executable.")
endif ()

if (notary_common_ENABLED AND utilities_ENABLED)
	add_subdirectory (utilities)
else ()
	message ("Disabled building utilities executables.")
endif ()
