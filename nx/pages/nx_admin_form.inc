<?php


function nx_admin_form ($form, &$form_state) {
	
	drupal_add_library('system', 'drupal.collapse');
	
	// get action parameters
	$action = nx_get_action();

	

	
	$form = array();
		
	//======================================		MOD UPDATES
	
	module_load_include('inc', 'nx', 'nx_lib_setup');
	
	$mods = nx_get_mods(true);
	foreach ($mods as $m => $data) {
		$outdated = ($mods[$m]['lastdate']>-1 && $mods[$m]['curversion'] < $mods[$m]['lastdate']);
		
		if ($mods[$m]['lastdate'] > -1) {
			$mods[$m]['lastdate'] = str_replace('[', '<font color=gray>', str_replace(']', '</font>', date ('Y-m-d [H:i:s]', $mods[$m]['lastdate'])));	
			if ($mods[$m]['curversion'] == 0) $mods[$m]['curversion'] = '<i>- not installed -</i>';
			else $mods[$m]['curversion'] = str_replace('[', '<font color=gray>', str_replace(']', '</font>',  $mods[$m]['curversion'])); //date ('Y-m-d [H:i:s]', $mods[$m]['curversion'])));
		} else {
			$mods[$m]['lastdate'] = '<font color=silver><i>- no files -</i></font>';
			$mods[$m]['curversion'] = '<font color=silver><i>- no files -</i></font>';
		}
		
		
		if ($outdated) {
			$mods[$m]['curversion'] = '<font color=maroon>'.$mods[$m]['curversion'].'</font>';
			$mods[$m]['actions'] = nx_action_link('update', 'mod', $m, false, 'admin/config/nx/core/update');
		} else $mods[$m]['actions'] = '';
	}
	$form ['mods'] = array(
		'#type' => 'tableselect',
		'#title' => 'Enabled NX Modules',
		'#header' => array ('mod' => 'Mods', 'curversion' => 'Your version', 'lastdate' => 'File last modified', 'actions' => 'Actions'),
		'#options' => $mods,
	);		
		
	//======================================		USER TAGS
	/*
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
	*/
	

	
	return $form;
}

function nx_admin_form_world_input_line ($universes, $wid, $wname, $wtag, $wuniversename = '') {
	$uni_list = '<select class="form-select" name="world_universe">';
	$universes = array_merge(array(-1 => ''), $universes);
	foreach ($universes as $wuid=>$wuname) {
		$uni_list .= '<option value="'.$wuid.'" '.($wuname == $wuniversename?'selected':'').'>'.$wuname.'</option>';
	}
	$uni_list .= '</select>';
		
	return array (
		'universe' => '<input type="hidden" name="world_id" value="'.$wid.'">'.$uni_list,
		'name' => '<input class="form-text" name="world_name" value="'.$wname.'">', 
		'owner' => $wtag,
		'actions' => '<input class="form-submit" type="submit" value="Save" style="margin-bottom: 0px;">',
	);	
}


function nx_admin_form_validate ($form, &$form_state) {
	if (isset($_POST['world_id'])) {
		$universe = $_POST['world_universe'];
		$name = $_POST['world_name'];
		
		$process = true;
		if ($universe < 1) {
			form_set_error('universe', 'Must select a universe.');
			$process = false;
		}
		if (empty(trim($name))) {
			form_set_error('world', 'World name cannot be empty.');
			$process = false;
		}
		if ($process) {
			form_set_error('yargl', 'TODO: do stuff');			
		}
	}
}

function nx_admin_form_submit ($form, &$form_state) {

}

