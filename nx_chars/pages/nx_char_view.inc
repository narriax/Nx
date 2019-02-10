<?php

function nx_char_view () {
	$char_id = nx_var('char');
	if ($char_id < 0) {
		drupal_goto('chars');
		return '';
	}
	
	if (array_key_exists('nx_char', $_GET) && $_GET['nx_char'] != $char_id) {
		nx_var_set('char', $_GET['nx_char']);
		drupal_goto('char');
	}
	
	module_load_include ('inc', 'nx_chars', 'api/nxChar');
	$char = nxChar::get_char($char_id, array('*'));
	if ($char == null) {
		$t = '<div class="messages error">Character not found ['.$char_id.']. <a href="chars">Return to character list?</a></div>';
		return $t;
	}
	
	if (count($_POST) > 0) {
		foreach ($_POST as $prop => $val) {
			if (empty($val)) continue;
			$temp = explode(':', $prop);
			$char->set_property($temp[0], $temp[1], $val);
		}
		drupal_goto('char');
	}
	
	dpm($char);
	
	drupal_set_title ('Character - '.$char->alias);
	
	$t = '<table class="metainfo">';
		$t .= '<tr><td>Owner: </td><td>'.$char->owner_tag.'</td></tr>';
		$t .= '<tr><td>Access: </td><td>'.$char->accessname.'</td></tr>';
		$t .= '<tr><td>Created: </td><td>'.$char->date_created.'</td></tr>';
		$t .= '<tr><td>Last modified: </td><td>'.$char->date_modified.'</td></tr>';
		$t .= '</table>';
	
	$all_props = nxChar::get_all_char_properties($char->wid);
	$edit_category = (array_key_exists('edit_section', $_GET)?$_GET['edit_section']:'');
	
	foreach ($all_props as $prop_group => $props) {
		$editing = ($edit_category === $prop_group);
		if (!$editing && $prop_group === 'name') {
			// TODO: special case display names differently
			
			//continue;
		}
		
		$options = array();
		if (empty($prop_group)) $t .= '<h4>Other</h4>';		
		else $t .= '<h4>'.ucfirst($prop_group).'</h4>';		
		if (!$editing) {
			$t .= '<div class="edit_section"><a href="?edit_section='.$prop_group.'">edit</a></div>';
		}
		
		if ($editing) $t .= '<form method=post>';
		$t .= '<table>';	
		foreach ($props as $pid => $prop) {		
			if ($editing || array_key_exists($prop->name, $char->properties)) {
				$t .= '<tr>';
				$t .= '<td>'.ucfirst($prop->name).': </td>';
				$t .= '<td>';
				
				$vals = array();
				if (array_key_exists($prop->name, $char->properties)) $vals = $char->properties[$prop->name]['values'];
				
				if ($editing) {
					$vals[-1] = '';
					foreach ($vals as $vid => $value) {
						$t .= '<input name="'.$vid.':'.$prop->id.'" value="'.$value.'"> ';
					}
				} else $t .= implode(',', $vals);
				$t .= '</td>';
				$t .= '</tr>';
			}
		}
		$t .= '</table>';
		if ($editing) $t .= '<input type=submit value=Save></form>';
	}
	
	return $t;
}