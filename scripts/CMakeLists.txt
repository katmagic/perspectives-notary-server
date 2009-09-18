
set (notary_script_SOURCES
		check_daemon.sh
		default_backup_db.sh
		default_check_daemons.sh
		default_create_db.sh
		default_create_keys.sh
		default_initialize.sh
		default_maintenance.sh
		default_refresh_db.sh
		default_start_daemons.sh
		default_stop_daemons.sh
		default_tail_logs.sh
		http_fetch.sh
		init_db_from_text.sh
		init_key_pair.sh
		list_by_last_obs.py
		run_backup.sh
		run_scan.sh
		start_daemon.sh
		start_db_manager.sh
		start_http_server.sh
		start_ondemand_listener.sh
		stop_daemon.sh
		stop_db_manager.sh
		stop_http_server.sh
		stop_ondemand_listener.sh)

foreach (notary_script_SOURCE ${notary_script_SOURCES})
	
	get_filename_component (
			notary_script_NAME
			${notary_script_SOURCE} NAME_WE)
	
	configure_file (
			${notary_script_SOURCE}
			${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}${notary_script_NAME}
			@ONLY)
	
	install (
			PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}${notary_script_NAME}
			DESTINATION ${notary_bin_PATH})
	
endforeach ()
