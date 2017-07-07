<?php

function nx_admin_tags_form ($form, &$form_state) {
		
	drupal_add_library('system', 'drupal.collapse');
	
	$form = array();
	
	module_load_include ('inc', 'nx', 'api/nxUser');
	$users = nxUser::get_users();
	$usrtags = nxUser::get_user_tags(false);
	$unclaimed_tags = array_diff($usrtags, array_keys($users));	
	
		
	$taginfo = nxUser::get_tag_info($unclaimed_tags);
		
	
	$form['unclaimed_tags'] = array (
		'#type' => 'fieldset',
		'#title' => 'Unclamed tags',
		'#prefix' => '<br>',
	);		

	if (empty($unclaimed_tags)) {
		$form['unclaimed_tags']['unclaimed_tags_msg'] = array (
			'#markup' => 'no unclaimed tags found',
		);
		return $form;
	}
	
	$form['unclaimed_tags']['clear_selected'] = array (
		'#type' => 'submit',
		'#name' => 'clear_selected',
		'#value' => 'Clear Selected',
	);	
	$form['unclaimed_tags']['clear_all'] = array (
		'#type' => 'submit',
		'#name' => 'clear_all',
		'#value' => 'Clear All',
	);
	
	$form['unclaimed_tags']['unclaimed_tags_list'] = array (
		'#type' => 'tableselect',
		'#header' => array (
			'uid' => array ('data' => '#'),
			'tag' => array ('data' => 'Tag'),
			'created' => array ('data' => 'Date created'),
			'modified' => array ('data' => 'Last modified'),
		),
		'#options' => array (),
	);
	
	foreach ($taginfo as $tag => $tagdata) {
		$form['unclaimed_tags']['unclaimed_tags_list']['#options'][$tagdata->tag] = array (
			'uid' => $tagdata->uid,
			'tag' => $tag,
			'created' => $tagdata -> date_created,
			'modified' => $tagdata -> date_modified,
		);
	}
	
	return $form;
}


function nx_admin_tags_form_submit ($form, &$form_state) {
	$button = $form_state['triggering_element']['#name'];
	
	if ($button == 'clear_all' || $button == 'clear_selected') {
		$taglist = array();
		if ($button == 'clear_all') {
			$taglist = array_keys($form_state['values']['unclaimed_tags_list']);
		} elseif ($button == 'clear_selected') {
			foreach ($form_state['values']['unclaimed_tags_list'] as $tag => $seton) {
				if ($seton !== 0) $taglist[] = $tag;
			}
		}
		
		if (empty($taglist)) {
			drupal_set_message('No tags to clear.');
			return;
		}
		
		module_load_include ('inc', 'nx', 'api/nxUser');
		nxUser::delete_tags($taglist);
	}
}
