
<?php

function nx_projects_config_form ($form, &$form_state) {
	
	if (!db_table_exists('nx_projects')) {
		dpm('TODO: make new table');
	}
	$q = db_select('nx_projects', 'p') 
	   -> fields('p', array());
	$q -> leftjoin ('nx_projects_sharing', 'ps', 'ps.prjid=p.id');
	$q -> addField('ps', 'username', 'shared_with');
	$q -> addField('ps', 'status', 'shared_with_status');
	$rows = $q -> execute ()-> fetchAllAssoc('id');

	if (count($rows) > 0) {
		$t = '<table><tr>';
		foreach ($rows[array_keys($rows)[0]] as $h => $v) {
			if ($h == 'shared_with_status') continue;
			$t .= '<th>'.strtoupper(str_replace('_', ' ', $h)).'</th>';
		}
		$t .= '</tr>';
		foreach ($rows as $r => $row) {
			$t .= '<tr>';
			foreach ($row as $h => $v) {
				if ($h == 'shared_with_status') continue;
				if ($h == 'shared_with') {
					$t .= '<td>'.$v;
					if (!empty($v)) $t .= ' ['.($row->shared_with_status == 0 ? 'no' : 'yes').']';
					$t .= '</td>';
				}
				else $t .= '<td>'.$v.'</td>';
			}			
			$t .= '</tr>';
		}
		$t .= '</table><br>';
		$form ['table'] = array (
			'#markup' => $t,
		);
	}
	
	$form ['new_project_name'] = array (
		'#title' => 'Project Name: ',
		'#type' => 'textfield',		
	);	
	$form ['new_project_db'] = array (
		'#title' => 'Use DB:',
		'#type' => 'textfield',		
	);
	
	$form ['submit'] = array (
		'#type' => 'submit',
		'#value' => 'Add',
	);
	
	return $form;
}


function nx_projects_config_form_validate ($form, &$form_state) {
	
	$name = $form_state['values']['new_project_name'];
	if (empty ($name)) {
		form_error ($form['new_project_name'], 'Name cannot be empty');
		return;
	}
	
	$q = db_select('nx_projects', 'p') -> fields('p', array());
	$rows = $q -> execute ()-> fetchAllAssoc('id');
	if (array_key_exists($id, $rows)) {
		form_error ($form['new_project_id'], 'Duplicate ID');
		return;		
	}

	return $form;
}


function nx_projects_config_form_submit ($form, &$form_state) {
	
	global $user;
	$q = db_select('nx_projects', 'p') -> fields('p', array());
	$rows = $q -> execute ()-> fetchAllAssoc('id');
	
	$name = $form_state['values']['new_project_name'];
	$db = $form_state['values']['new_project_db'];
	
	$id = userPrefix().'_'.strtolower(str_replace(' ', '', $name));
	if (strlen($id) > 16)
		$id = noVowels($id);
	if (strlen($id) > 16)
		$id = substr($id, 0, 16);
	if (array_key_exists($id, $rows)) {
		$id = substr($id, 0, 14);
		$i = 2;
		while (array_key_exists($id.str_pad($i,2,'0',STR_PAD_LEFT), $rows)) 
			$i ++;
		$id = $id.str_pad($i,2,'0',STR_PAD_LEFT);
	}
	
	$q = db_insert('nx_projects') -> fields(array(
		'id' => $id, 
		'name' => $name, 
		'db' => $db,
		'author' => $user->name,
	));
	$q -> execute ();

	return $form;
}

