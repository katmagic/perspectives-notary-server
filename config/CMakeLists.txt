
set (notary_configuration_SOURCES
		http_server_config.txt
		http_servers.txt
		scanner_blacklist.txt
		scanner_config.txt)

foreach (notary_configuration_SOURCE ${notary_configuration_SOURCES})
	
	get_filename_component (
			notary_configuration_NAME
			${notary_configuration_SOURCE} NAME)
	
	configure_file (
			${notary_configuration_SOURCE}
			${CMAKE_CURRENT_BINARY_DIR}/${notary_configuration_NAME}
			@ONLY)
	
	install (
			FILES ${CMAKE_CURRENT_BINARY_DIR}/${notary_configuration_NAME}
			DESTINATION ${notary_etc_PATH})
	
endforeach ()
