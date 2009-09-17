
set (script_NAMES
		build.sh
		create_deploy_dir.sh
		gen_key_pair.sh
		http_fetch.sh
		init_db_from_text.sh
		list_by_last_obs.py
		package_dist.sh
		package_full_dist.sh
		package_src_server.sh
		package_update_server.sh
		run_backup.sh
		run_scan.sh
		start_all.sh
		start_db_manager.sh
		start_http_server.sh
		start_ondemand_listener.sh
		stop_all.sh
		stop_db_manager.sh
		stop_http_server.sh
		stop_ondemand_listener.sh
		update_deploy.dir.sh)

foreach (script_NAME ${script_NAMES})
	
	configure_file (
			${script_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}${script_NAME} @ONLY)
	
	install (
			PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${notary_bin_PREFIX}${script_NAME}
			DESTINATION ${notary_bin_PATH})
	
endforeach ()
