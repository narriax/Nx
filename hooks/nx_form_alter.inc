<?php

function nx_form_alter (&$form, &$form_state) {
	//dpm($form);
	//dvm( $form['#form_id']);
	
	
	switch ($form['#form_id']) {
		
		case 'user_admin_account':								// add custom fields to the admin's people table
			nx_form_alter__people_table($form, $form_state);
			break;
			
		case 'user_register_form':								// require names, generate user tag upon registration
			nx_form_alter__registration ($form, $form_state);
			//dpm($form['#validate']);
			break;
			
		case 'user_profile_form':
			nx_form_alter__profile ($form, $form_state);		// edit names, and user tag in user profile
			break;
	}
	
}



// ======================================================================
/*
 *
 */
function nx_form_alter__profile (&$form, &$form_state) {
	if (!array_key_exists('account',$form)) return;
	
	nx_form_alter__profile_fields ($form, $form_state);
}

// ======================================================================
/*
 *
 */
function nx_form_alter__registration (&$form, &$form_state) {
	if (!array_key_exists('account',$form)) return;
	
	nx_form_alter__profile_fields ($form, $form_state);
	
}

// ======================================================================
/*
 *
 */
function nx_strip_string ($str) {
	$str = str_replace(' ','',$str);
	$str = preg_replace("/[^ \w]+/", "", $str);
	$str = filter_var ( trim($str), FILTER_SANITIZE_STRING, FILTER_FLAG_STRIP_LOW | FILTER_FLAG_STRIP_HIGH);
	$str = filter_var ( trim($str), FILTER_SANITIZE_SPECIAL_CHARS, FILTER_FLAG_STRIP_LOW | FILTER_FLAG_STRIP_HIGH);
	return $str;
}

/*
 *
 */
function nx_generate_tag ($fname, $lname) {
	$ftoken = '';
	$ftokenlong = '';
	$ltoken = '';
	
	$fcount = 0;
	$fcountlong = 0;
	$vowels = 'aeiouy';
	
	if (empty($lname)) {
		$fcount = 1;
	} else {
		// if last name starts with a vowel, search for first consonant in the first name
		if (strpos($vowels, strtolower($lname[0])) !== false) {
			for ($i=0; $i < strlen($fname); $i++) {
				$fcount++;
				if (strpos($vowels, strtolower($fname[$i])) === false) break;
			}
			for ($i=0; $i < strlen($fname); $i++) {
				$fcountlong++;
				if (strpos($vowels, strtolower($fname[$i])) === false && $fcountlong > $fcount) break;
			}
			
			
		// if last name starts with a consonant, search for the first vowel in the first name
		} else {
			for ($i=0; $i < strlen($fname); $i++) {
				$fcount++;
				if (strpos($vowels, strtolower($fname[$i])) !== false) break;
			}
			for ($i=0; $i < strlen($fname); $i++) {
				$fcountlong++;
				if (strpos($vowels, strtolower($fname[$i])) !== false && $fcountlong > $fcount) break;
			}
		}
		
		if (strlen($lname)>5) $ltoken = substr ($lname,0,5);
		else $ltoken = $lname;
	}
	
	if (!empty($fname)) {
		$ftoken = substr($fname,0,$fcount);
		if ($fcountlong > $ftoken) $ftokenlong = substr($fname,0,$fcountlong);
	}
	
	$options = array();
	$options[] = $ftoken.$ltoken;
	if (!empty($ftokenlong)) $options[] = $ftokenlong.$ltoken;
	if (strlen($lname) > strlen($ltoken) && $lname[strlen($ltoken)] == 's') {
		$options[] = $ftoken.$ltoken.'s';
		if (!empty($ftokenlong)) $options[] = $ftokenlong.$ltoken.'s';
	}
	if (!empty($ftokenlong) && strlen($ltoken)>3) $options[] = $ftokenlong.substr($ltoken,0,3);
	if (!empty($ftokenlong) && strlen($ltoken)>2) $options[] = $ftokenlong.substr($ltoken,0,2);
	
	dvm('TODO -- allow variations: '. implode(', ', $options));
	
	return strtolower($options[0]);
}


/*
 *
 */
function nx_form_alter__profile_fields (&$form, &$form_state) {
	if (!array_key_exists('account',$form)) return;
	
	
	// fetch ajax values
	$tag = '';
	$require_fields = true;
	if (array_key_exists('values', $form_state)) {
		if (array_key_exists('override_required', $form_state['values']) && $form_state['values']['override_required'] === 1) $require_fields = false;		
		if (!empty($form_state['values']['tag'])) $tag = $form_state['values']['tag'];
	}
	
	
	// form override section (admin only)
	$form['overrides'] = array (
		'#type' => 'fieldset',
		'#title' => 'Overrides',
		'#weight' => -30,
		'#access' => user_access('administer site configuration'),
	);
	$form['overrides']['override_required'] = array (
		'#type' => 'checkbox',
		'#title' => 'suppress [required] condition',
		'#ajax' => array(
		  'callback' => 'nx_form_alter__profile_fields_ajax_overrides',
		  'wrapper' => 'name-group-wrapper',
		  'method' => 'replace',
		  'effect' => 'fade',
		  '#limit_validation_errors' => array(),
		),				
	);
	
	// add user names and tag to the form
	$form['account']['name-group'] = array (
		'#type' => 'fieldset',
		'#prefix' => '<div id="name-group-wrapper">',
		'#suffix' => '</div>',		
		'#weight' => -20,
	);
	$form['account']['name-group']['firstname'] = array (
		'#type' => 'textfield',
		'#title' => t('First Name'),
		'#maxlength' => 60,
		'#description' => $form['account']['name']['#description'],
		'#required' => $require_fields,
		'#attributes' => array('class' => array ('name', 'firstname')),
		'#default_value' => '',
		'#access' => TRUE,
		'#ajax' => array(
		  'callback' => 'nx_form_alter__profile_fields_ajax_name',
		  'wrapper' => 'name-tag-wrapper',
		  'method' => 'replace',
		  'effect' => 'fade',
		),		
	);
	$form['account']['name-group']['lastname'] = array (
		'#type' => 'textfield',
		'#title' => t('Last Name'),
		'#maxlength' => 60,
		'#description' => $form['account']['name']['#description'],
		'#required' => $require_fields,
		'#attributes' => array('class' => array ('name', 'lastname')),
		'#default_value' => '',
		'#access' => TRUE,
		'#ajax' => array(
		  'callback' => 'nx_form_alter__profile_fields_ajax_name',
		  'wrapper' => 'name-tag-wrapper',
		  'method' => 'replace',
		  'effect' => 'fade',
		),			
	);	
	$form['account']['name-group']['tag'] = array (
		'#type' => 'textfield',
		'#title' => t('Tag'),
		'#maxlength' => 16,
		'#description' => 'Generated automatically from name.',
		'#required' => $require_fields,
		'#attributes' => array('class' => array ('name', 'tag')),
		'#default_value' => $tag,
		'#access' => TRUE,
		'#prefix' => '<div id="name-tag-wrapper">',
		'#suffix' => '</div>',			
	);	
	if (!user_access('administer site configuration')) {
		$form['account']['name-group']['tag']['#attributes']['readonly'] = 'readonly';
		$form['account']['name-group']['tag']['#attributes']['class'][] = 'readonly';
	}
	
	$form['account']['name']['#maxlength'] = 32;
	$form['account']['name']['#description'] = t('Spaces and punctuation are not allowed except for underscores.');	
	$form['account']['name']['#attributes']['class'][] = 'name';
	
	$form['#validate'][] = 'nx_form_alter__profile_fields_validate';
	$form['#submit'][] = 'nx_form_alter__profile_fields_submit';	
}
 

/*
 *
 */
function nx_form_alter__profile_fields_ajax_overrides ($form, &$form_state) {
	if (array_key_exists('firstname', $form_state['input'])) $form_state['values']['firstname'] = $form_state['input']['firstname'];
	if (array_key_exists('lastname', $form_state['input'])) $form_state['values']['lastname'] = $form_state['input']['lastname'];
	if (array_key_exists('tag', $form_state['input'])) $form_state['values']['tag'] = $form_state['input']['tag'];
	return $form['account']['name-group'];
} 
 

/*
 *
 */
function nx_form_alter__profile_fields_ajax_name ($form, &$form_state) {
	$fname = $lname = '';
	
	if (!empty($form_state['values']['firstname'])) $fname = ucfirst($form_state['values']['firstname']);
	elseif (!empty($form_state['input']['firstname'])) $fname = ucfirst($form_state['input']['firstname']);
	
	if (!empty($form_state['values']['lastname'])) $lname = ucfirst($form_state['values']['lastname']);
	elseif (!empty($form_state['input']['lastname'])) $lname = ucfirst($form_state['input']['lastname']);
		
	if (!empty($fname) || !empty($lname)) $form['account']['name-group']['tag']['#value'] = nx_generate_tag(nx_strip_string($fname), nx_strip_string($lname));
	
	return $form['account']['name-group']['tag'];
}


/*
 *
 */
function nx_form_alter__profile_fields_validate ($form, $form_state) {
	$require_fields = true;
	if (array_key_exists('override_required', $form_state['values']) && $form_state['values']['override_required'] === 1) $require_fields = false;	
	
	
    if ($error = user_validate_name($form_state['values']['firstname'])) {
		if (empty($form_state['values']['firstname'])) {
			if ($require_fields) form_set_error ('tag', t('First name is required.'));
		} else form_set_error('firstname', t('First name contains an illegal character.'));
    }	
    if ($error = user_validate_name($form_state['values']['lastname'])) {
		if (empty($form_state['values']['lastname'])) {
			if ($require_fields) form_set_error ('tag', t('Last name is required.'));
		} else form_set_error('lastname', t('Last name contains an illegal character.'));
    }	
	
	if ($require_fields && empty($form_state['values']['tag'])) {
		form_set_error ('tag', t('Tag is required.'));
	}

}

/*
 *
 */
function nx_form_alter__profile_fields_submit ($form, $form_state) {
	$uid = $form_state['values']['uid'];
	if ($uid < 1) return;
	module_load_include('inc', 'nx', 'api/nxUser');
	$u = nxUser::get_user_by_id($uid);
	if ($u == null) return;
	
	$u->update_tag($form_state['values']['tag']);
}


// ======================================================================
function nx_form_alter__people_table (&$form, &$form_state) {
	if (!array_key_exists('accounts',$form)) return;
	
	module_load_include ('inc', 'nx', 'api/nxUser');
	$users = nxUser::get_users();
	$usrtags = nxUser::get_user_tags(false);
	
	//dpm($users);
	
	$new_headers = array (
		'tags' => array('data' => 'Tags'),	
		'fullname' => array ('data' => 'Name'),
	);
	$form['accounts']['#header'] = array_merge (
		array ('uid' => array ('data' => '#')),
		array_slice($form['accounts']['#header'],0,1),
		$new_headers,
		array_slice($form['accounts']['#header'],1));
	
	
	foreach ($form['accounts']['#options'] as $uid => $udata) {
		$form['accounts']['#options'][$uid]['uid'] = $uid;
		$form['accounts']['#options'][$uid]['fullname'] = 'TODO';
		if (array_key_exists($uid, $usrtags)) {
			$form['accounts']['#options'][$uid]['tags'] = '<b>'.$usrtags[$uid].'</b>';
		} else $form['accounts']['#options'][$uid]['tags'] = '';
	}
	
	return $form;
}

