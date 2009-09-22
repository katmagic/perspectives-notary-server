
set (notary_common_SOURCES
		bdb_storage.c
		file_list_convert.c
		flex_queue.c
		keyscan_util.c
		net_util.c
		notary_crypto.c
		notary_util.c
		patricia.c
		server_common.c)

set (notary_common_INCLUDE_DIR
		${CMAKE_CURRENT_SOURCE_DIR}
		${bdb_INCLUDE_DIR}
		${openssl_INCLUDE_DIR}
		${crypto_INCLUDE_DIR})
set (notary_common_INCLUDE_DIR
		${notary_common_INCLUDE_DIR}
		PARENT_SCOPE)

set (notary_common_LIBRARIES
		${notary_lib_PREFIX}common
		${bdb_LIBRARIES}
		${openssl_LIBRARIES}
		${crypto_LIBRARIES}
		dl pthread
		PARENT_SCOPE)

add_library (${notary_lib_PREFIX}common
		${notary_common_SOURCES})

include_directories (
		${notary_common_INCLUDE_DIR}
		${additional_INCLUDE_DIR})
