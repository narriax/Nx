<?php


function nx_admin_form ($form, &$form_state) {
	
	drupal_add_library('system', 'drupal.collapse');
	
	// get action parameters
	$action = nx_get_action();

	
	
	/*
	module_load_include('inc', 'nx', 'api/nxTreeTable');
	$tree = new nxTreeTable();
	
	$tree->AddCategory('universe');
	$tree->SetCategoryHeaders('universe', array('_' => 'Universe', 'owner_tag' => 'Owner (Tag)', 'access' => 'Access'));
	$tree->SetCategoryActions('universe', array('toggle', 'edit', 'delete'));
	$tree->SetCategoryDB('universe', 'nx_worlds_universes');
	
	$tree->AddCategory('world', 'universe');
	$tree->SetCategoryHeaders('world', array('_' => 'World', 'owner_tag' => 'Owner (Tag)', 'access' => 'Access'));
	$tree->SetCategoryActions('world', array('toggle', 'edit', 'delete'));
	$tree->SetCategoryDB('world', 'nx_worlds', 'universe_id');
	
	$tree->FetchItems();
	dpm($tree);
	*/
	
	$form = array();
		
	//======================================		MOD UPDATES
	
	module_load_include('inc', 'nx', 'nx_lib_setup');
	
	if ($action && $action->action == 'update' && $action->domain == 'mod') {
		$mod_arg = $action->arg;
		nx_mod_setup__smart_update($mod_arg);
	}
	
	$mods = nx_get_mods(true);
	foreach ($mods as $m => $data) {
		$outdated = $mods[$m]['curversion'] < $mods[$m]['lastdate'];
		
		$mods[$m]['lastdate'] = str_replace('[', '<font color=gray>', str_replace(']', '</font>', date ('Y-m-d [h:i:s]', $mods[$m]['lastdate'])));	
		if ($mods[$m]['curversion'] == 0) $mods[$m]['curversion'] = '<i>- not installed -</i>';
		else $mods[$m]['curversion'] = str_replace('[', '<font color=gray>', str_replace(']', '</font>', date ('Y-m-d [h:i:s]', $mods[$m]['curversion'])));
		if ($outdated) {
			$mods[$m]['curversion'] = '<font color=maroon>'.$mods[$m]['curversion'].'</font>';
			$mods[$m]['actions'] = nx_action_link('update', 'mod', $m);
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
	
	//======================================		WORLDS
	module_load_include ('inc', 'nx', 'api/nxWorld');
	
	// delete doomed worlds
	if ($action && $action->action == 'delete' && $action->domain == 'world') {
		if ($doomed = nxWorld::get_world_by_id($action->arg)) {
			$doomed->delete();
		}
	}	
	
	// get all existing worlds
	$universes = nxWorld::get_universes();	
	$worldlist = nxWorld::get_worlds();
	$form['panel_worlds'] = array (
		'#type' => 'fieldset',
		'#title' => 'Worlds',
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	// list all existing worlds to a table
	$temp_edit_arg = -1;
	if ($action && $action->action == 'edit' && $action->domain == 'world') $temp_edit_arg = $action->arg;
	$world_options = array ();
	foreach ($worldlist as $wid => $w) {
		if ($temp_edit_arg == $wid) {			
			$world_options[$wid] = nx_admin_form_world_input_line ($universes, $wid, $w->name, $w->owner_tag, $w->universe->name);	
		} else {
			$world_options[$wid] = array (
				'universe' => $w->universe->name,
				'name' => $w->name,
				'owner' => $w->owner_tag,
				'actions' => nx_action_link('edit', 'world', $wid).' &nbsp; '.nx_action_link('delete', 'world', $wid),
			);
		}
	}
	// add ui to to create new world
	if ($action && $action->action == 'addnew' && $action->domain == 'world') {
		module_load_include ('inc', 'nx', 'api/nxUser');
		if ($me = nxUser::get_current_user()) {		
			$world_options['new'] = nx_admin_form_world_input_line ($universes, 'new', '', $me->tag);
		}
	}
	
	//publish table to the form
	$form['panel_worlds']['worlds'] = array (
		'#type' => 'tableselect',
		'#header' => array ('universe' => 'Universe', 'name' => 'World', 'owner' => 'Owner (tag)', 'actions' => ''),
		'#options' => $world_options,
		'#suffix' => nx_action_link('add new', 'world'),
	);	
	
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

