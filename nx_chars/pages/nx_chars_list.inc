<?php

function nx_chars_list () {
	
	$world_id = nx_cur_world ();
	if ($world_id < 0) {
		drupal_goto('nx_worlds');
		return '';
	}
	
	
	module_load_include ('inc', 'nx_chars', 'api/nxChar');
	$char_list = nxChar::get_chars($world_id);
	//dpm($char_list);
	
	
	$t = '<table><tr><th>Universe</th><th>World</th><th>Alias</th></tr>';
	foreach ($char_list as $cid => $char) {
		$t .= '<tr>';
		$t .= '<td>'.$char->world->universe->name.'</td>';
		$t .= '<td>'.$char->world->name.'</td>';
		$t .= '<td>'.$char->alias.'</td>';
		$t .= '</tr>';
	}
	$t .= '</table>';
	
	return $t;
}