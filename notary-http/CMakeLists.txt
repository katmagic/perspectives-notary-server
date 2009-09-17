
set (notary_http_server_SOURCES
		notary_http.c
		parse.c)

add_executable (${notary_bin_PREFIX}http_server
		${notary_http_server_SOURCES})

include_directories (
		${notary_common_INCLUDE_DIR}
		${additional_INCLUDE_DIR})

target_link_libraries (${notary_bin_PREFIX}http_server
		${notary_common_LIBRARIES}
		${additional_LIBRARIES})

install (
		TARGETS ${notary_bin_PREFIX}http_server
		RUNTIME DESTINATION ${notary_bin_PATH})
