
set (notary_client_SOURCES
		client_policy.c
		client_test.c
		contact_notary.c
		notary_local.c)

set (notary_client_INCLUDE_DIR
		${notary_SOURCE_DIR}/notary-client
		${notary_common_INCLUDE_DIR})
set (notary_client_INCLUDE_DIR
		${notary_client_INCLUDE_DIR}
		PARENT_SCOPE)

set (notary_client_LIBRARIES
		notary-client
		${notary_common_LIBRARIES}
		PARENT_SCOPE)

add_library (notary-client
		${notary_client_SOURCES})

include_directories (
		${notary_client_INCLUDE_DIR})

set_source_files_properties (
		${notary_client_SOURCES}
		PROPERTIES
		COMPILE_FLAGS -std=gnu99)
