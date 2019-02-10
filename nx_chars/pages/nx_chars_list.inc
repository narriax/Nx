<?php

function nx_chars_list () {
	
	$world_id = nx_cur_world ();
	if ($world_id < 0) {
		nx_var_set('bounce_setworld', current_path());
		drupal_goto('worlds');
		return '';
	}
	
	
	module_load_include ('inc', 'nx_chars', 'api/nxChar');
	$char_list = nxChar::get_chars($world_id, array('color'));
	dpm($char_list);
	
	
	$t = '<table><tr><th>Owner</th><th>Alias</th><th>Properties</th><th>Actions</th></tr>';
	foreach ($char_list as $cid => $char) {
		$t .= '<tr>';
		
		$authoring_tooltip = "Access: ".$char->accessname."\nCreated: ".$char->date_created."\nModified: ".$char->date_modified;
		$t .= '<td><div title="'.$authoring_tooltip.'">'.$char->owner_tag.'</div></td>';
		
		$t .= '<td><a href="char?nx_char='.$cid.'">'.$char->alias.'</a></td>';
		$t .= '<td>';
		ksort($char->properties);
		foreach ($char->properties as $propname => $prop) {
			echo $prop['name'].' = '.implode(',', $prop['values']).'<br>';
		}
		$t .= '</td>';
		
		$t .= '<td>?..</td>';
		$t .= '</tr>';
	}
	$t .= '</table>';
	
	return $t;
}