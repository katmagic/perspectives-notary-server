
set (notary_ssl_scanner_SOURCES
		apps.c
		openssl.c)

add_executable (notary-ssl-scanner
		${notary_ssl_scanner_SOURCES})

include_directories (
		${openssl_INCLUDE_DIR})

target_link_libraries (notary-ssl-scanner
		${openssl_LIBRARIES})
