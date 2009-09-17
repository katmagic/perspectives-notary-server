
set (configuration_NAMES
		http_config.txt
		http_servers.txt
		scanner_blacklist.txt
		scanner_config.txt)


foreach (configuration_NAME ${configuration_NAMES})
	
	configure_file (
			${configuration_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${configuration_NAME} @ONLY)
	
	install (
			FILES ${CMAKE_CURRENT_BINARY_DIR}/${configuration_NAME}
			DESTINATION ${notary_etc_PATH})
	
endforeach ()
