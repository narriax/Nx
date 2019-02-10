<?php

function nx_chars_list () {
	
	$world_id = nx_cur_world ();
	if ($world_id < 0) {
		nx_var_set('bounce_setworld', current_path());
		drupal_goto('worlds');
		return '';
	}
	
	
	module_load_include ('inc', 'nx_chars', 'api/nxChar');
	$char_list = nxChar::get_chars($world_id);
	dpm($char_list);
	
	
	$t = '<table><tr><th>Owner</th><th>Alias</th></tr>';
	foreach ($char_list as $cid => $char) {
		$t .= '<tr>';
		$t .= '<td>'.$char->owner_tag.($char->accessname != null?' ('.$char->accessname.')':'').'</td>';
		$t .= '<td>'.$char->alias.'</td>';
		$t .= '</tr>';
	}
	$t .= '</table>';
	
	return $t;
}