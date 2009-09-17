
set (notary_db_manager_SOURCES
		notary_db_manager.c)

add_executable (${notary_bin_PREFIX}db-manager
		${notary_db_manager_SOURCES})

include_directories (
		${notary_common_INCLUDE_DIR}
		${additional_INCLUDE_DIR})

target_link_libraries (${notary_bin_PREFIX}db-manager
		${notary_common_LIBRARIES}
		${additional_LIBRARIES})

set_source_files_properties (
		${notary_db_manager_SOURCES}
		PROPERTIES
		COMPILE_FLAGS -std=gnu99)

install (
		TARGETS ${notary_bin_PREFIX}db-manager
		RUNTIME DESTINATION ${notary_bin_PATH})


set (report_observation_SOURCES
		report_observation.c)

add_executable (${notary_bin_PREFIX}report-observation
		${report_observation_SOURCES})

target_link_libraries (${notary_bin_PREFIX}report-observation
		${notary_common_LIBRARIES}
		${additional_LIBRARIES})

set_source_files_properties (
		${report_observation_SOURCES}
		PROPERTIES
		COMPILE_FLAGS "-std=gnu99")

install (
		TARGETS ${notary_bin_PREFIX}report-observation
		RUNTIME DESTINATION ${notary_bin_PATH})


configure_file (
		scripts/ssl_scan ${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssl_scan @ONLY)

configure_file (
		scripts/ssl_scan_bash.sh ${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssl_scan_bash.sh @ONLY)

configure_file (
		scripts/ssl_scan_python.py ${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssl_scan_python.py @ONLY)

install (
		PROGRAMS
			${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssl_scan
			${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssl_scan_python.py
			${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssl_scan_bash.sh
		DESTINATION ${notary_bin_PATH})


configure_file (
		scripts/ssh_scan ${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssh_scan @ONLY)

configure_file (
		scripts/ssh_scan_bash.sh ${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssh_scan_bash.sh @ONLY)

configure_file (
		scripts/ssh_scan_python.py ${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssh_scan_python.py @ONLY)

install (
		PROGRAMS
			${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssh_scan
			${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssh_scan_python.py
			${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}ssh_scan_bash.sh
		DESTINATION ${notary_bin_PATH})
