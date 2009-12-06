
cmake_minimum_required (VERSION 2.6)


project (notary)


set (CMAKE_CONFIGURATION_TYPES
		"Release"
		CACHE INTERNAL "" FORCE)

set (CMAKE_BUILD_TYPE
		Release
		CACHE STRING "Build type. Available options: ${CMAKE_CONFIGURATION_TYPES}" FORCE)


set (CMAKE_INSTALL_PREFIX
		""
		CACHE INTERNAL "" FORCE)

set (CMAKE_EXE_LINKER_FLAGS
		""
		CACHE INTERNAL "" FORCE)

set (BUILD_SHARED_LIBS
		OFF
		CACHE INTERNAL "" FORCE)


file (STRINGS VERSION notary_VERSION)


set (bdb_PREFIX
		$ENV{bdb_PREFIX})

set (openssl_PREFIX
		$ENV{openssl_PREFIX})

if (bdb_PREFIX)
	message ("bdb_PREFIX specified as ${bdb_PREFIX} .")
	set (bdb_INCLUDE_DIR_SEARCH
			${bdb_PREFIX}/include)
	set (bdb_LIBRARIES_SEARCH
			${bdb_PREFIX}/lib)
else ()
	set (bdb_INCLUDE_DIR_SEARCH
			/usr/include /usr/local/include
			/opt/include /opt/local/include)
	set (bdb_LIBRARIES_SEARCH
			/lib
			/usr/lib /usr/local/lib
			/opt/lib /opt/local/lib)
endif ()

if (openssl_PREFIX)
	message ("openssl_PREFIX specified as ${openssl_PREFIX} .")
	set (openssl_INCLUDE_DIR_SEARCH
			${openssl_PREFIX}/include)
	set (openssl_LIBRARIES_SEARCH
			${openssl_PREFIX}/lib)
else ()
	set (openssl_INCLUDE_DIR_SEARCH
			/usr/include /usr/local/include
			/opt/include /opt/local/include)
	set (openssl_LIBRARIES_SEARCH
			/lib
			/usr/lib /usr/local/lib
			/opt/lib /opt/local/lib)
endif ()


find_path (bdb_INCLUDE_DIR db.h
		HINTS ${bdb_INCLUDE_DIR_SEARCH})

find_library (bdb_LIBRARIES db
		HINTS ${bdb_LIBRARIES_SEARCH})

find_path (openssl_INCLUDE_DIR openssl/ssl.h
		HINTS ${openssl_INCLUDE_DIR_SEARCH})

find_library (openssl_LIBRARIES ssl
		HINTS ${openssl_LIBRARIES_SEARCH})

find_path (crypto_INCLUDE_DIR openssl/crypto.h
		HINTS ${openssl_INCLUDE_DIR_SEARCH})

find_library (crypto_LIBRARIES crypto
		HINTS ${openssl_LIBRARIES_SEARCH})

set (additional_INCLUDE_DIR
		CACHE PATH "Additional folders for including.")

set (additional_LIBRARIES
		CACHE FILEPATH "Additional libraries for linking.")


find_program (bash_EXEC bash
		HINTS
			/bin
			/usr/bin /usr/local/bin
			/opt/bin /opt/local/bin)

if (${bash_EXEC} STREQUAL bash_EXEC-NOTFOUND)
	message (FATAL_ERROR "Bash executable not found.")
endif ()

find_program (python_EXEC python
		HINTS
			/bin
			/usr/bin /usr/local/bin
			/opt/bin /opt/local/bin)

if (${python_EXEC} STREQUAL python_EXEC-NOTFOUND)
	message (FATAL_ERROR "Python executable not found.")
endif ()


set (notary_common_ENABLED
		ON
		CACHE BOOL "Enable building common.")

set (notary_http_server_ENABLED
		ON
		CACHE BOOL "Enable building http-server.")

set (notary_scanner_ENABLED
		ON
		CACHE BOOL "Enable building scanner.")

set (notary_utilities_ENABLED
		ON
		CACHE BOOL "Enable building utilities.")

set (notary_scripts_ENABLED
		ON
		CACHE BOOL "Enable building scripts.")

set (notary_configurations_ENABLED
		ON
		CACHE BOOL "Enable building configurations.")


set (notary_static_ENABLED
		OFF
		CACHE BOOL "Enable static linking.")

if (notary_static_ENABLED)
	
	set (BUILD_SHARED_LIBS
		OFF
		CACHE INTERNAL "" FORCE)
	
	set (CMAKE_EXE_LINKER_FLAGS
		-all-static
		CACHE INTERNAL "" FORCE)
	
else ()
	
	set (BUILD_SHARED_LIBS
		OFF
		CACHE INTERNAL "" FORCE)
	
	set (CMAKE_EXE_LINKER_FLAGS
		""
		CACHE INTERNAL "" FORCE)
	
endif ()


set (notary_PATH
		"/tmp/notary_${notary_VERSION}"
		CACHE PATH "Prefix for the installation folders.")

set (notary_PATH_MANGLING
		""
		CACHE STRING "Extra-prefix for some installation folders (resulting in /etc/notary, /var/lib/notary, /var/run/notary, etc.)")


set (CMAKE_INSTALL_PREFIX
		"${notary_PATH}"
		CACHE INTERNAL "" FORCE)


set (notary_bin_PREFIX
		"notary_${notary_VERSION}_"
		CACHE STRING "Prefix of the executable files (those in bin).")

set (notary_libexec_PREFIX
		"notary_${notary_VERSION}_"
		CACHE STRING "Prefix of the (internal) executable files (those in libexec).")

set (notary_lib_PREFIX
		"notary_${notary_VERSION}_"
		CACHE STRING "Prefix of the library files.")


set (notary_bin_PATH
		"${notary_PATH}/bin"
		CACHE PATH "Path of the executable files (bin).")

set (notary_libexec_PATH
		"${notary_PATH}/libexec"
		CACHE PATH "Path of the (internal) executable files (libexec).")


if (notary_PATH_MANGLING)
	
	set (notary_etc_PATH
			"${notary_PATH}/etc/${notary_PATH_MANGLING}"
			CACHE PATH "Path of the configuration files (etc).")
	
	set (notary_var_PATH
			"${notary_PATH}/var"
			CACHE PATH "Generic path of the data files (var).")
	
	set (notary_data_PATH
			"${notary_var_PATH}/lib/${notary_PATH_MANGLING}"
			CACHE PATH "Path of the durable data files (var/lib).")
	
	set (notary_run_PATH
			"${notary_var_PATH}/run/${notary_PATH_MANGLING}"
			CACHE PATH "Path of the temporary data files (var/run).")
	
	set (notary_backups_PATH
			"${notary_var_PATH}/backups/${notary_PATH_MANGLING}"
			CACHE PATH "Path of the backup files (var/backup).")
	
	set (notary_log_PATH
			"${notary_var_PATH}/log/${notary_PATH_MANGLING}"
			CACHE PATH "Path of the log files (var/log).")
	
else ()
	
	set (notary_etc_PATH
			"${notary_PATH}/etc"
			CACHE PATH "Path of the configuration files (etc).")
	
	set (notary_var_PATH
			"${notary_PATH}/var"
			CACHE PATH "Generic path of the data files (var).")
	
	set (notary_data_PATH
			"${notary_var_PATH}/lib"
			CACHE PATH "Path of the durable data files (var/lib).")
	
	set (notary_run_PATH
			"${notary_var_PATH}/run"
			CACHE PATH "Path of the temporary data files (var/run).")
	
	set (notary_backups_PATH
			"${notary_var_PATH}/backups"
			CACHE PATH "Path of the backup files (var/backups).")
	
	set (notary_log_PATH
			"${notary_var_PATH}/log"
			CACHE PATH "Path of the log files (var/log).")
	
endif ()


set (notary_private_key_PATH
		"${notary_etc_PATH}/private_key.pem"
		CACHE PATH "Path of the private key.")

set (notary_public_key_PATH
		"${notary_etc_PATH}/public_key.pem"
		CACHE PATH "Path of the public key.")

set (notary_db_PATH
		"${notary_data_PATH}/db"
		CACHE PATH "Path of the BerkeleyDB environment.")

set (notary_db_NAME
		"notary.db"
		CACHE STRING "Name of the BerkeleyDB name.")

set (notary_http_listen_IP
		"0.0.0.0"
		CACHE STRING "Listening IP of the notary http server.")

set (notary_http_listen_PORT
		"8080"
		CACHE STRING "Listening port of the notary http server.")

set (notary_new_request_socket_PATH
		"${notary_run_PATH}/new_request"
		CACHE PATH "Unix domain socket path for new requests.")

set (notary_finished_request_socket_PATH
		"${notary_run_PATH}/finished_request"
		CACHE PATH "Unix domain socket path for finished requests.")


if (notary_common_ENABLED)
	add_subdirectory (common)
else ()
	message ("Disabled building common library.")
endif ()

if (notary_http_server_ENABLED)
	add_subdirectory (http_server)
else ()
	message ("Disabled building http-server.")
endif ()

if (notary_scanner_ENABLED)
	add_subdirectory (scanner)
else ()
	message ("Disabled building scanner.")
endif ()

if (notary_utilities_ENABLED)
	add_subdirectory (utilities)
else ()
	message ("Disabled building utilities.")
endif ()

if (notary_scripts_ENABLED)
	add_subdirectory (scripts)
else ()
	message ("Disabled building scripts.")
endif ()

if (notary_configurations_ENABLED)
	add_subdirectory (config)
else ()
	message ("Disabled building configurations.")
endif ()
