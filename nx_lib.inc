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


function nx_action_link ($action, $domain='', $arg='', $warn=false, $url = '') {
	$l = str_replace('_', '', str_replace(' ','',$action));
	if (!empty($domain)) $l .= '_'.$domain;
	if (!empty($arg)) $l .= ':'.$arg;
	
	if (!empty($url)) $url = url($url);
	
	return '<a class="actionlink '.($warn?'warn':'').'" href="'.$url.'?action='.$l.'">'.$action.'</a>';
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
	if (empty($tablealias)) return $q;
	
	module_load_include('inc', 'nx', 'api/nxUser');
	$usr = nxUser::get_cur_user();
	if (in_array('god', $usr->roles)) return $q;
	
	$and = db_and();
	foreach ($tablealias as $ta => $table) {
		$q -> leftJoin ('nx_access', 'acs_'.$ta, 'acs_'.$ta.'.accessid='.$ta.'.accessid');
					
		$or = db_or()
		    -> isNull ($ta.'.owner_tag')	// shared
			-> isNull ($ta.'.accessid')		// shared
		    -> condition ($ta.'.owner_tag', $usr->tag)		// owned by this user
			-> condition ('acs_'.$ta.'.alid', 0);			// public
			
		$whites = db_and ()
			-> isNotNull ('acs_'.$ta.'.whiteusers')
			-> condition ('acs_'.$ta.'.whiteusers', '%['.$usr->tag.']%', 'LIKE');
		$or->condition($whites);

		$blacks = db_or ()
			-> isNull ('acs_'.$ta.'.blackusers')
			-> condition ('acs_'.$ta.'.blackusers', '%['.$usr->tag.']%', 'NOT LIKE');
		
		$and->condition($or);
		$and->condition($blacks);
		// TODO: same domain and groups
	}
	$q -> condition($and);
	return $q;
}


function nx_db_get_cols ($tables = array()) {
	$q = db_select ('nx', 'nx') 
	   -> fields ('nx', array('item', 'cols'));
	if (empty($tables)) {
		$q -> isNotNull ('nx.cols');
	} else {
		for ($i=0; $i < count($tables); $i++) $tables[$i] = 'tables/'.$tables[$i].'.sql';
		$and = db_and() -> condition ('nx.item', $tables, 'IN') -> isNotNull ('nx.cols');
		$q -> condition ($and);
	}
	if (!$results = $q->execute()->fetchAll()) {
		return array();
	} 
	
	$allcols = array ();
	foreach ($results as $r) {
		$t = str_replace('.sql', '', str_replace('tables/', '', $r->item));
		$allcols[$t] = unserialize($r->cols);
	}
	return $allcols;
}

