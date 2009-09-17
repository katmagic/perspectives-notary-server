
set (configuration_NAMES
		client_params.txt
		http_notary_list.txt
		http_server_config.txt
		notary_list.txt
		probing_blacklist.txt
		scanner_config.txt
		server_config.txt)

foreach (configuration_NAME ${configuration_NAMES})
	
	configure_file (
			${configuration_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${configuration_NAME} @ONLY)
	
	install (
			FILES ${CMAKE_CURRENT_BINARY_DIR}/${configuration_NAME}
			DESTINATION ${notary_etc_PATH})
	
endforeach ()
