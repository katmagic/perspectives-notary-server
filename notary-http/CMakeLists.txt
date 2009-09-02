
set (notary_http_SOURCES
		notary_http.c
		parse.c)

add_executable (notary-http
		${notary_http_SOURCES})

include_directories (
		${notary_common_INCLUDE_DIR}
		${additional_INCLUDE_DIR})

target_link_libraries (notary-http
		${notary_common_LIBRARIES}
		${additional_LIBRARIES})
