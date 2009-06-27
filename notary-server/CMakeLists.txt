
set (notary_server_SOURCES
		server.c)

add_executable (notary-server
		${notary_server_SOURCES})

include_directories (
		${notary_common_INCLUDE_DIR}
		${additional_INCLUDE_DIR})

target_link_libraries (notary-server
		${notary_common_LIBRARIES}
		${additional_LIBRARIES})
