
set (utility_NAMES
		db2file
		db_search
		db_speed_test
		dump_b64_signature
		file2db
		request_scan
		signature_util
		update_timespans_test)

foreach (utility_NAME ${utility_NAMES})
	
	add_executable (${notary_bin_PREFIX}${utility_NAME}
			${utility_NAME}.c)
	
	include_directories (
			${notary_common_INCLUDE_DIR}
			${additional_INCLUDE_DIR})
	
	target_link_libraries (${notary_bin_PREFIX}${utility_NAME}
			${notary_common_LIBRARIES}
			${additional_LIBRARIES})
	
	install (
			TARGETS ${notary_bin_PREFIX}${utility_NAME}
			RUNTIME DESTINATION ${notary_bin_PATH})
	
endforeach ()
