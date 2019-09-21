<?php

function nx_projects_page () {
	$brs = array (l('Home', ''));
	
	$t = '';
	if (count(arg()) < 2) {
		$rows_owned = getUserProjects();
		$rows_shared = getSharedProjects();
		if (count($rows_owned) < 1 && count($rows_shared) < 1) return 'No projects to show';
		
		$t .= '<b>My projects:</b><ul>';
		if (count($rows_owned) < 1)
			$t .= '<i>- none -</i>';
		foreach ($rows_owned as $rid => $row) {
			$t .= '<li>'.l($row->name, 'project/'.$rid);
			$t .= ' <font color=silver><small>('.$row->accessid.')</small></font>';
			$t .= '</li>';
		}
		$t .= '</ul>';
		
		$t .= l('+ Add a new project', 'projectadd');
		
		$t .= '<hr><b>Projects shared with me:</b><ul>';
		if (count($rows_shared) <= count($rows_owned))
			$t .= '<i>- none -</i>';
		foreach ($rows_shared as $rid => $row) {
			if (array_key_exists($rid, $rows_owned)) continue;
			$t .= '<li>'.l($row->name, 'project/'.$rid).' <font color=silver><small><i>[by '.$row->owner_tag.']</i></small></font></li>';
		}
		$t .= '</ul>';
		
		$brs[] = 'Projects';
		drupal_set_breadcrumb($brs);
		return $t;
		
	} else {
		$q = db_select('nx_projects', 'p') -> fields ('p', array()) -> condition('p.id', arg(1));
		$prj = $q->execute() -> fetch();
		
		$brs[] = l('Projects', 'project');
		if ($prj == null || empty($prj)) {
			$brs[] = '['.arg(1).']';
			return 'No such project found';
		}

		$brs[] = $prj->name;
		drupal_set_breadcrumb($brs);
				
		return drupal_get_form('nx_project_view_form', $prj);
	}
	
}


function nx_project_view_form ($form, &$form_state, $prj) {
	//dpm($prj);
	
	$form = array();
	
	$form['id'] = array (
		'#type' => 'hidden',
		'#value' => $prj->id,
	);
	
	$form['dates'] = array (
		'#markup' => '<div style="float: right;"><i>Created: &nbsp; '.$prj->date_created.'<br>Last edit: &nbsp; '.$prj->date_modified.'</div>',
	);
	
	$form['name'] = array (
		'#type' => 'textfield',
		'#default_value' => $prj->name,
		'#prefix' => '<h2>',
		'#suffix' => '</h2><br>',
	);
	$form['owner'] = array (
		'#markup' => ($prj->owner_tag != nx_tag() ? '<small><i>by ['.$prj->owner_tag.']</i></small>' : '')
	);
	
	$form['access'] = nx_access_form_controls();
	$form['access']['#default_value'] = $prj->accessid;

	$form['db'] = array (
		'#type' => 'textfield',
		'#title' => 'Database',
		'#default_value' => $prj->db,
	);

	$form['submit'] = array (
		'#type' => 'submit',
		'#value' => 'submit',
		'#prefix' => '<br>',
	);
	
	return $form;
}


function nx_project_view_form_submit ($form, $form_state) {
	$name = $form_state['values']['name'];
	$id = $form_state['values']['id'];
	$accessid = $form_state['values']['access'];
	$db = $form_state['values']['db'];
	
	$q = db_update('nx_projects') 
		-> fields (array('name' => $name, 'db' => $db, '	accessid' => $accessid)) 
		-> condition('id', $id);
	$q -> execute();
}

