
set (notary_db_manager_SOURCES
		notary_db_manager.c)

add_executable (${notary_bin_PREFIX}db_manager
		${notary_db_manager_SOURCES})

include_directories (
		${notary_common_INCLUDE_DIR}
		${additional_INCLUDE_DIR})

target_link_libraries (${notary_bin_PREFIX}db_manager
		${notary_common_LIBRARIES}
		${notary_static_LIBRARIES}
		${additional_LIBRARIES})

set_source_files_properties (
		${notary_db_manager_SOURCES}
		PROPERTIES COMPILE_FLAGS -std=gnu99)

install (
		TARGETS ${notary_bin_PREFIX}db_manager
		RUNTIME DESTINATION ${notary_bin_PATH})


set (notary_report_observation_SOURCES
		report_observation.c)

add_executable (${notary_libexec_PREFIX}report_observation
		${notary_report_observation_SOURCES})

target_link_libraries (${notary_libexec_PREFIX}report_observation
		${notary_common_LIBRARIES}
		${notary_static_LIBRARIES}
		${additional_LIBRARIES})

set_source_files_properties (
		${notary_report_observation_SOURCES}
		PROPERTIES COMPILE_FLAGS "-std=gnu99")

install (
		TARGETS ${notary_libexec_PREFIX}report_observation
		RUNTIME DESTINATION ${notary_libexec_PATH})


set (notary_scanner_bin_script_SOURCES
		ondemand_listener.py)

set (notary_scanner_libexec_script_SOURCES
		simple_scanner.py
		ssh_scan_bash.sh
		ssh_scan_python.py
		ssh_scan.sh
		ssl_scan_bash.sh
		ssl_scan_python.py
		ssl_scan.sh)

foreach (notary_scanner_script_SOURCE ${notary_scanner_bin_script_SOURCES})
	
	get_filename_component (
			notary_scanner_script_NAME
			${notary_scanner_script_SOURCE}
			NAME_WE)
	
	configure_file (
			${notary_scanner_script_SOURCE}
			${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}${notary_scanner_script_NAME}
			@ONLY)
	
	install (
			PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}${notary_scanner_script_NAME}
			DESTINATION ${notary_bin_PATH})
	
endforeach ()

foreach (notary_scanner_script_SOURCE ${notary_scanner_libexec_script_SOURCES})
	
	get_filename_component (
			notary_scanner_script_NAME
			${notary_scanner_script_SOURCE}
			NAME_WE)
	
	configure_file (
			${notary_scanner_script_SOURCE}
			${CMAKE_CURRENT_BINARY_DIR}/${notary_libexec_PREFIX}${notary_scanner_script_NAME}
			@ONLY)
	
	install (
			PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${notary_libexec_PREFIX}${notary_scanner_script_NAME}
			DESTINATION ${notary_libexec_PATH})
	
endforeach ()
