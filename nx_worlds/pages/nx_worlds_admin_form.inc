<?php


function nx_worlds_admin_form ($form, &$form_state) {
	
	
		//======================================		WORLDS
	if (!module_exists('nx_worlds')) return $form;
	module_load_include ('inc', 'nx_worlds', 'nxWorld');
	
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
	
	return $form();
}