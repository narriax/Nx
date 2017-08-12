<?php


function nx_var ($name = "") {
	if (empty($name)) return null;
	if (!array_key_exists('nx', $_SESSION)) return null;
	if (!array_key_exists($name, $_SESSION['nx'])) return null;
	return $_SESSION['nx'][$name];
}

/*
 *
 */
function nx_var_set ($name = "", $value = false) {
	if (empty($name)) return; 
	if (!array_key_exists('nx', $_SESSION)) $_SESSION['nx'] = array();
	$_SESSION['nx'][$name] = $value;
}


function nx_action_link ($action, $domain='', $arg='', $warn=false) {
	$l = str_replace('_', '', str_replace(' ','',$action));
	if (!empty($domain)) $l .= '_'.$domain;
	if (!empty($arg)) $l .= ':'.$arg;
	return '<a class="actionlink '.($warn?'warn':'').'" href="?action='.$l.'">'.$action.'</a>';
}


function nx_get_action () {
	if (!isset($_GET['action'])) return null;
		
	$action = new stdClass();
	$action->action = '';
	$action->domain = '';
	$action->arg = -1;
	
	$tokens = explode(':',$_GET['action']);
	if (count ($tokens) > 1) {
		$action->arg = $tokens[1];
	}
	
	$tokens[0] = explode('_',$tokens[0]);
	$action->action = $tokens[0][0];
	if (count ($tokens[0]) > 1) {
		$action->domain = $tokens[0][1];
	}
	
	return $action;
}


function nx_get_access_levels () {
	if (!$access_levels = nx_var('access_levels')) {
		$q = db_select('nx_access_levels', 'al') -> fields('al', array());
		$access_levels = $q->execute()->fetchAllKeyed(0,1);
		nx_var_set('access_levels', $access_levels);
	}
	return $access_levels;
}


function nx_db_limit_access (&$q, $tablealias) {
	$access_levels = nx_get_access_levels();
	//dpm($access_levels);
	
	module_load_include('inc', 'nx', 'api/nxUser');
	$usr = nxUser::get_current_user();
	//dpm($usr);
	
	dvm('TODO: nx_db_limit_access');
	
	return $q;
}


