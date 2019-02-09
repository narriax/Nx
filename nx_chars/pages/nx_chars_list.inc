<?php

function nx_chars_list () {
	
	$world_id = nx_cur_world ();
	if ($world_id < 0) {
		drupal_goto('nx_worlds');
		return '';
	}
	
	
	module_load_include ('inc', 'nx_chars', 'api/nxChar');
	$char_list = nxChar::get_chars($world_id);
	dpm($char_list);
	
	
	$t = '<table><tr><th>World</th><th>Alias</th><th>Owner</th></tr>';
	foreach ($char_list as $cid => $char) {
		$t .= '<tr>';
		$t .= '<td>'.ucfirst($char->world->universe->name).': '.ucfirst($char->world->name).'</td>';
		$t .= '<td>'.$char->alias.'</td>';
		$t .= '<td>'.$char->owner_tag.'</td>';
		$t .= '</tr>';
	}
	$t .= '</table>';
	
	return $t;
}