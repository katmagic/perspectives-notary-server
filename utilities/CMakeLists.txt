
set (notary_utility_NAMES
		db2file
		db_prime
		db_search
		db_speed_test
		dump_b64_signature
		file2db
		request_scan
		signature_util
		update_timespans_test)

foreach (notary_utility_NAME ${notary_utility_NAMES})
	
	add_executable (${notary_libexec_PREFIX}${notary_utility_NAME}
			${notary_utility_NAME}.c)
	
	include_directories (
			${notary_common_INCLUDE_DIR}
			${additional_INCLUDE_DIR})
	
	target_link_libraries (${notary_libexec_PREFIX}${notary_utility_NAME}
			${notary_common_LIBRARIES}
			${notary_static_LIBRARIES}
			${additional_LIBRARIES})
	
	install (
			TARGETS ${notary_libexec_PREFIX}${notary_utility_NAME}
			RUNTIME DESTINATION ${notary_libexec_PATH})
	
endforeach ()
