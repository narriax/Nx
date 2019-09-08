<?php

function nx_update_form ($form, &$form_state) {
	
	
	$mod_name = '';
	$action = nx_get_action();
	if ($action && $action->action == 'update' && $action->domain == 'mod') {
		$mod_name = $action->arg;
	}
	if (empty($mod_name)) {
		$form['msg'] = array ( '#markup' => 'Nothing to update.' );
		return $form;
	}
	
	module_load_include('inc', 'nx', 'nx_lib_setup');
	$info = nx_mod_setup__smart_update_status($mod_name);
	
	
	$table_options = array();
	foreach ($info['all_tables'] as $item => $tname) {
		$table_options[$item] = array (
			'item' => $tname,
			'status' => '<b>'.$info['status'][$item].'</b>',
		);		
		if (array_key_exists($item, $info['system'])) {
			$table_options[$item]['system'] = $info['system'][$item];
		} else $table_options[$item]['system'] = '-';
		if (array_key_exists($item, $info['available'])) {
			$table_options[$item]['available'] = date('Y-m-d H:i:s', $info['available'][$item]);
		} else $table_options[$item]['available'] = '-';
	}
	
	
	$form['tables'] = array (
		'#type' => 'fieldset', 
		'#title' => '<b>'.$mod_name.'</b>: Tables',
	);
	
	$form['tables']['all'] = array (
		'#type' => 'tableselect', 
		'#title' => 'Status',
		'#header'=> array ('item' => 'Table', 'status' => 'Status', 'system' => 'System version', 'available' => 'Available version'),
		'#options' => $table_options,
	);	
	foreach ($form['tables']['all']['#options'] as $i => $data) {
		if ($info['status'][$i] == 'OK') {
			$form['tables']['all'][$i]['#disabled'] = true;
		}
	}
	
	return $form;
}