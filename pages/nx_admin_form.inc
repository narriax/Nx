<?php

function nx_admin_form ($form, &$form_state) {
	
	drupal_add_library('system', 'drupal.collapse');
	
	$form = array();
	
	//======================================
	module_load_include ('inc', 'nx', 'api/nxUser');
	$userlist = nxUser::get_users();
	$form['panel_users'] = array (
		'#type' => 'fieldset',
		'#title' => 'User Tags',
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	$table = '<table><tr><th>TAG</th><th>username</th></tr>';
	foreach ($userlist as $t => $u) {
		$table .= '<tr>';
		$table .= '<td><b>'.$u->tag.'</b></td>';
		$table .= '<td>'.$u->username.'</td>';
		$table .= '</tr>';
	}
	$table .= '</table>';
	$form['panel_users']['user_list'] = array (
		'#markup' => $table,
	);
	
	
	//======================================
	module_load_include ('inc', 'nx', 'api/nxWorld');
	$worldlist = nxWorld::get_worlds();
	$form['panel_worlds'] = array (
		'#type' => 'fieldset',
		'#title' => 'Worlds',
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	$table = '<table><tr><th>UNIVERSE</th><th>WORLD</th><th>OWNER</th></tr>';
	foreach ($worldlist as $wid => $w) {
		$table .= '<tr>';
		$table .= '<td><b>'.$w->universe->name.'</b></td>';
		$table .= '<td>'.$w->name.'</td>';
		if (!isset($w->owner_tag)) $table .= '<td>-</td>';
		else $table .= '<td>'.$w->owner_tag.'</td>';
		$table .= '</tr>';
	}
	$table .= '</table>';
	$form['panel_worlds']['user_list'] = array (
		'#markup' => $table,
	);	
	
	
	return $form;
}