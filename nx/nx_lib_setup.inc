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
		} else $setup_files[$module_name][$f] = filemtime($setupfolder.'/'.$f);
	}
	nx_var_set('mod_setup_files', $setup_files);
	return $setup_files[$module_name];
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
	
	$q = db_select ('nx', 'nx') -> fields ('nx', array('module', 'date_modified')) -> condition('nx.item', '%_vno', 'LIKE');
	$mod_versions = $q -> execute() -> fetchAllKeyed(0,1);
	nx_var_set('mod_cur_versions', $mod_versions);
	return $mod_versions;
}


function nx_get_mods ($force_refresh = false) {
	$setup_files = nx_all_mods_setup_timestamps($force_refresh);
	$mod_versions = nx_all_mods_installed_version($force_refresh);
	
	$shortlist = array ();
	foreach ($setup_files as $m => $files) {
		if (empty($m)) continue;
		$shortlist[$m] = array (
			'mod' => $m, 
			'lastdate' => empty($files)?"-1":max($files), 
			'curversion' => (array_key_exists($m, $mod_versions)?$mod_versions[$m]:'0')
		);
	}	
	return $shortlist;
}


function nx_mod_setup__smart_update_status ($mod_name) {
	dvm("TODO: update $mod_name tables by comparing file dates to nx table values");	
	$file_timestamps = nx_get_mod_setup_timestamps ($mod_name);
	
	$and = db_and () -> condition ('nx.module', $mod_name) -> condition ('nx.item', '%_vno', 'NOT LIKE');
	$q = db_select ('nx', 'nx') 
		-> fields ('nx', array()) 
		-> condition ($and);
	
	$system_timestamps = array();
	if ($results = $q -> execute() -> fetchAll()) {
		foreach ($results as $r) {
			if ($r->item == $mod_name.'_vno') continue;
			$system_timestamps[$r->item] = $r->date_modified;
		}
	}
	$all = array_merge($system_timestamps, $file_timestamps);
	$all = array_keys($all);
	asort($all);
	
	$all_tables = array ();
	$all_scripts = array ();
	$all_status = array();
	foreach ($all as $item) {
		if (strlen($item) > 4 && substr($item,-4) === '.sql') {
			$all_tables[$item] = str_replace('.sql', '', str_replace('tables/', '', $item));
		} else if (strlen($item) > 4 && substr($item,-4) === '.inc') {
			$all_scripts[$item] = array (str_replace('.inc', '', $item));
		} else {
			dvm ("smart_update: unknown item type [".$item."]");
		}
		
		$sys = -1;
		if (array_key_exists($item, $system_timestamps)) {
			$sys = $system_timestamps[$item];
		}
		
		$ava = -1;
		if (array_key_exists($item, $file_timestamps)) {
			$ava = $file_timestamps[$item];
		}		
		
		if ($ava < 0 && $sys >= 0) {
			$all_status[$item] = 'delete';
		} else if ($sys < 0) {
			$all_status[$item] = 'new';
		} else if ($sys < date('Y-m-d H:i:s', $ava)) {
			$all_status[$item] = 'update';
		} else {
			$all_status[$item] = 'OK';
		}		
		
	}
	
	return array(
		'system' => $system_timestamps,
		'available' => $file_timestamps,
		'all_tables' => $all_tables,
		'all_scripts' => $all_scripts,
		'status' => $all_status,
	);
	
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
		nx_mod_setup__update_tables ($module_name, $module_setup_dir);
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
function nx_mod_setup__update_tables ($module_name, $module_setup_dir, $sql_files = array(), $directives = array ('CREATE TABLE', 'ALTER TABLE', 'INSERT INTO')) {
	
	$sql_dir = $module_setup_dir.'/tables';
	if (empty($sql_files)) $sql_files = scandir ($sql_dir);
	

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
	
	
	// record what we did in DB
	$latest = 0;
	foreach ($sql_files as $sql) {
		if (strlen($sql)<5 || substr($sql,-4) !== '.sql') continue;
		
		$file_date = filemtime($sql_dir.'/'.$sql);
		if ($file_date > $latest) $latest = $file_date;
		$file_date = date('Y-m-d H:i:s', $file_date);
		$item = 'tables/'.$sql;
		$table = str_replace('.sql', '', $sql);	
		$cols = serialize(nx_get_db_columns($table));
		
		$current = db_query("SELECT * FROM nx WHERE ((module=:modname) AND (item=:item) ) LIMIT 1", array (':modname' => $module_name, ':item' => $item))->fetch();

		if (!$current) {
			db_query("INSERT INTO {nx} (module, item, date_modified, cols) VALUES (:modname, :item, :date, :cols)",
				array (':modname' => $module_name, ':item' => $item, ':date' => $file_date, ':cols' => $cols));				
		} else {
			$current->cols = unserialize($current->cols);
			//dpm($current, 'current');			
			dvm('TODO: handle updates');
		}
	}
	
	$current = db_query("SELECT * FROM nx WHERE ((module=:modname) AND (item=:item) ) LIMIT 1", array (':modname' => $module_name, ':item' => $module_name.'_vno'))->fetch();
	if (!$current) {
		db_query("INSERT INTO {nx} (module, item, date_modified) VALUES (:modname, :item, :date)",
			array (':modname' => $module_name, ':item' => $module_name.'_vno', ':date' => date('Y-m-d H:i:s', $latest)));
	} else {
		db_query("UPDATE {nx}  SET date_modified = :date WHERE (module = :modname AND item = :item)",
			array (':modname' => $module_name, ':item' => $module_name.'_vno', ':date' => date('Y-m-d H:i:s', $latest)));		
	}
	
}


function nx_get_db_columns ($table) {
	$schema = db_query ("select COLUMN_NAME, COLUMN_TYPE from INFORMATION_SCHEMA.COLUMNS where TABLE_NAME='".$table."'")->fetchAll();
	$cols = array();
	foreach ($schema as $s) {
		$cols[$s->COLUMN_NAME] = $s->COLUMN_TYPE;
	}
	return $cols;
}

