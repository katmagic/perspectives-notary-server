
set (notary_scanner_SOURCES
		notary_scanner.c)

add_executable (notary-scanner
		${notary_scanner_SOURCES})

include_directories (
		${notary_common_INCLUDE_DIR})

target_link_libraries (notary-scanner
		${notary_common_LIBRARIES})

set_source_files_properties (
		${notary_scanner_SOURCES}
		PROPERTIES
		COMPILE_FLAGS -std=gnu99)
