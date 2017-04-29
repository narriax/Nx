<?php


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
function nx_mod_setup__update_tables ($sql_dir) {
	$sql_files = scandir ($sql_dir);
	
	// apply directives in this order
	$markers = array ('CREATE TABLE', 'ALTER TABLE', 'INSERT INTO');
	
	foreach ($markers as $marker) {
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

