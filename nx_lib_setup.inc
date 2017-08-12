<?php


function nx_get_mod_setup_timestamps ($module_name) {
	$setup_files = nx_var('mod_setup_files');
	if ($setup_files == null) $setup_files = array();
	$setup_files[$module_name] = array();
	
	$setupfolder = nx_module_setup_folder($module_name);
	$files = scandir ($setupfolder);
	
	$latest_date = 0;
	foreach ($files as $f) {
		if ($f === '.' || $f === '..') continue;
		
		if (!is_file($setupfolder.'/'.$f)) {
			
			$subfiles = scandir ($setupfolder.'/'.$f);
			foreach ($subfiles as $sf) {
				if (!is_file($setupfolder.'/'.$f.'/'.$sf)) continue;
				$setup_files[$module_name][$f.'/'.$sf] = filemtime($setupfolder.'/'.$f.'/'.$sf);
			}
		}
		$setup_files[$module_name][$f] = filemtime($setupfolder.'/'.$f);
	}
	nx_var_set('mod_setup_files', $setup_files);
}


function nx_all_mods_setup_timestamps ($force_refresh = false) {
	$setup_files = nx_var('mod_setup_files');
	if ($force_refresh) $setup_files = array();
	if (!empty($setup_files)) return $setup_files;
	
	$modules = module_list();
	
	foreach ($modules as $m) {
		if ((strlen($m) < 3 && $m !== 'nx') || (strlen($m) >= 3 && substr($m, 0, 3) !== 'nx_')) continue;
		nx_get_mod_setup_timestamps($m);
	}
	$setup_files = nx_var('mod_setup_files');
	return $setup_files;
}


function nx_all_mods_installed_version ($force_refresh = false) {
	$mod_versions = nx_var('mod_cur_versions');
	if ($force_refresh) $mod_versions = array();
	if (!empty($mod_versions)) return $mod_versions;
	
	$q = db_select ('nx', 'nx') -> fields ('nx', array('module', 'date_modified')) -> condition('nx.table_name', '%_vno', 'LIKE');
	$mod_versions = $q -> execute() -> fetchAllKeyed(0,1);
	nx_var_set('mod_cur_versions', $mod_versions);
	return $mod_versions;
}


function nx_get_mods ($force_refresh = false) {
	$setup_files = nx_all_mods_setup_timestamps($force_refresh);
	$mod_versions = nx_all_mods_installed_version($force_refresh);
	
	$shortlist = array ();
	foreach ($setup_files as $m => $files) {
		$shortlist[$m] = array (
			'mod' => $m, 
			'lastdate' => max($files), 
			'curversion' => (array_key_exists($m, $mod_versions)?$mod_versions[$m]:'0')
		);
	}	
	return $shortlist;
}


function nx_mod_setup__smart_update ($mod_name) {
	dvm("TODO: update $mod_name tables by comparing file dates to nx table values");	
	//nx_mod_setup__update_tables();
}


// perform module setup
function nx_mod_setup ($module_name, $module_setup_dir) {

	global $nx_setup;

	// load all setup files for the module
	// this will populate setup array
	nx_mod_load_files ($module_setup_dir);
	
	// if setup array did not populate, exit
	if (!array_key_exists($module_name, $nx_setup)) return;
	$setup = $nx_setup[$module_name];
	
	// create user roles
	if (array_key_exists('roles', $setup)) {
		nx_mod_setup__update_roles($setup['roles']);
	}
	
	// create tables
	if (file_exists($module_setup_dir.'/tables')) {
		nx_mod_setup__update_tables ($module_setup_dir.'/tables');
	}
	
	variable_set ($module_name.'_setup', 1);
	// variable_set ($module_name.'_version', 1);		TODO
}

// create / update user roles
function nx_mod_setup__update_roles ($update_roles) {
	foreach ($update_roles as $role_name => $role_weight) {			
		// load or create new
		$role_exists = true;
		if (!$role = user_role_load_by_name($role_name)) {
			$role = new stdClass();
			$role->name = $role_name;
			$role_exists = false;
		}
		
		// update & write
		$role->weight = $role_weight;
		
		// by rights, should use {user_role_save($role)}, but its bugged, so write our own quick update		
		if ($role_exists) {
			$q = db_update ('role')
				-> condition ('name', $role->name) 
				-> fields (array(
					'weight' => $role->weight,
				));
		} else {
			$q = db_insert('role')
				-> fields (array (
					'name' => $role->name, 
					'weight' => $role->weight,
				));
		}
		$q -> execute();

	}
}


// automatically import tables from sql dumps
function nx_mod_setup__update_tables ($sql_dir, $sql_files = array(), $directives = array ('CREATE TABLE', 'ALTER TABLE', 'INSERT INTO')) {
	if (empty($sql_files)) $sql_files = scandir ($sql_dir);
	dpm($sql_files);
	
	
	// apply directives in this order
	foreach ($directives as $marker) {
		foreach ($sql_files as $sql) {
			if (strlen($sql)<5 || substr($sql,-4) !== '.sql') continue;
			$raw = file_get_contents($sql_dir.'/'.$sql);	
			while (strpos($raw,$marker) !== false) {
				$raw = substr($raw, strpos($raw,$marker));
				$token = substr($raw, 0, strpos ($raw, ';')+1);
				$raw = substr($raw, strpos($raw,';')+1);
				
				db_query($token);
			}
		}
	}
}

