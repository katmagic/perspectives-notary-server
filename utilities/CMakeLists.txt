
set (utilities_PREFIXES
#		convert_to_timespans
		db2file
		db_multiaccess_test
		db_search
		db_speed_test
		dump_b64_signature
		file2db
		full_client
		gen_mozilla_sig
		gen_svg
		load_test_client
		request_scan
		signature_util
		simple_client
		test_policy
		test_policy_fake
		update_timespans_test)

foreach (PREFIX ${utilities_PREFIXES})
	
	add_executable (${PREFIX}
			${PREFIX}.c)
	
	include_directories (
			${notary_client_INCLUDE_DIR}
			${additional_INCLUDE_DIR})
	
	target_link_libraries (${PREFIX}
			${notary_client_LIBRARIES}
			${additional_LIBRARIES})
	
endforeach ()
