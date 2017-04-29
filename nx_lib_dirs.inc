<?php


// return the name of the module based on the .module file path
function nx_mod_name ($script_path) {
	$this_script = explode('\\', $script_path);
	$module_name = $this_script[count($this_script)-1];
	$module_name = substr($module_name,0,strpos($module_name,'.'));
	return $module_name;
}


// load files in the specified directory if variable conditions  are met
function nx_mod_load_files ($dir, $conditions = array(), $file_ext = '.inc') {
	// if dir does not exist, exit
	if (!file_exists($dir)) return;
	
	// if conditions are passed, and are not met, exit
	foreach ($conditions as $var => $value) {
		if (variable_get($var) != $value) return;
	}
	
	$files = scandir ($dir);
	foreach ($files as $f) {
		if (substr($f,-4) === $file_ext) include_once($dir .'/'.$f);	
	}
}


// initialize the module based on the .module file path
function nx_mod_initialize ($script_path) {
	// identify this module
	$module_name = nx_mod_name($script_path);
	$mod_dir = drupal_get_path('module', $module_name);
	
	// check setup
	$setup_dir = DRUPAL_ROOT.'/'.$mod_dir.'/setup';
	if (file_exists($setup_dir) && variable_get ($module_name.'_setup') != 1) {
		module_load_include('inc', 'nx', 'nx_lib_setup');
		nx_mod_setup ($module_name, $setup_dir);
	}
	
	// include hooks
	$hooks_dir = DRUPAL_ROOT.'/'.$mod_dir.'/hooks';
	nx_mod_load_files ($hooks_dir);
	
}

