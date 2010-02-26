
set (notary_bin_script_SOURCES
		backup_db.sh
		check_daemons.sh
		control.sh
		create_db.sh
		create_keys.sh
		http_fetch.sh
		initialize.sh
		maintenance.sh
		prime_db.sh
		refresh_db.sh
		start_daemons.sh
		stop_daemons.sh
		tail_logs.sh)

set (notary_libexec_script_SOURCES
		check_user.sh
		check_daemon.sh
		init_db_from_text.sh
		init_key_pair.sh
		list_by_last_obs.py
		run_backup.sh
		run_prime.sh
		run_scan.sh
		start_daemon.sh
		stop_daemon.sh)

foreach (notary_script_SOURCE ${notary_bin_script_SOURCES})
	
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

foreach (notary_script_SOURCE ${notary_libexec_script_SOURCES})
	
	get_filename_component (
			notary_script_NAME
			${notary_script_SOURCE} NAME_WE)
	
	configure_file (
			${notary_script_SOURCE}
			${CMAKE_CURRENT_BINARY_DIR}/${notary_libexec_PREFIX}${notary_script_NAME}
			@ONLY)
	
	install (
			PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${notary_libexec_PREFIX}${notary_script_NAME}
			DESTINATION ${notary_libexec_PATH})
	
endforeach ()
