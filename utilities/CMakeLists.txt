
set (utilities_PREFIXES
		db2file
		db_search
		db_speed_test
		dump_b64_signature
		file2db
		request_scan
		signature_util
		update_timespans_test)

foreach (PREFIX ${utilities_PREFIXES})
	
	add_executable (${PREFIX}
			${PREFIX}.c)
	
	include_directories (
			${notary_common_INCLUDE_DIR}
			${additional_INCLUDE_DIR})
	
	target_link_libraries (${PREFIX}
			${notary_common_LIBRARIES}
			${additional_LIBRARIES})
	
endforeach ()
