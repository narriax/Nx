<?php

function nx_form_alter (&$form, &$form_state) {
	//dpm($form);
	
	if ($form['#form_id'] == 'user_admin_account') {
		nx_form_alter__people_table($form, $form_state);
	}
}




function nx_form_alter__people_table (&$form, &$form_state) {
	
	if (!array_key_exists('accounts',$form)) return;
	
	module_load_include ('inc', 'nx', 'api/nxUser');
	$usrtags = nxUser::get_user_tags();
	
	$new_headers = array (
		'tags' => array('data' => 'Tags'),	
	);
	$form['accounts']['#header'] = array_merge (
		array_slice($form['accounts']['#header'],0,1),
		$new_headers,
		array_slice($form['accounts']['#header'],1));
	
	
	foreach ($form['accounts']['#options'] as $uid => $udata) {
		if (array_key_exists($uid, $usrtags)) {
			$form['accounts']['#options'][$uid]['tags'] = '<b>'.implode(', ', $usrtags[$uid]).'</b>';
		} else $form['accounts']['#options'][$uid]['tags'] = '';
	}
	return $form;
}