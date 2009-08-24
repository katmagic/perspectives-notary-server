
set (scan_db_manager_SOURCES
		scan_db_manager.c)

add_executable (scan-db-manager
		${scan_db_manager_SOURCES})

include_directories (
		${notary_common_INCLUDE_DIR}
		${additional_INCLUDE_DIR})

target_link_libraries (scan-db-manager
		${notary_common_LIBRARIES}
		${additional_LIBRARIES})

set_source_files_properties (
		${scan_db_manager_SOURCES}
		PROPERTIES
		COMPILE_FLAGS -std=gnu99)

set (report_observation_SOURCES
		report_observation.c)

add_executable (report-observation
		${report_observation_SOURCES})

target_link_libraries (report-observation
		${notary_common_LIBRARIES}
		${additional_LIBRARIES})

set_source_files_properties (
		${report_observation_SOURCES}
		PROPERTIES
		COMPILE_FLAGS "-std=gnu99")
