
set (notary_http_SOURCES
		notary_http.c
		parse.c)

add_executable (notary-http
		${notary_http_SOURCES})

include_directories (
		${notary_client_INCLUDE_DIR})

target_link_libraries (notary-http
		${notary_client_LIBRARIES})
