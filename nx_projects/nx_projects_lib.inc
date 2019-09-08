
<?php




function noVowels ($str) {
	return str_replace('a', '', str_replace('e', '', str_replace('o', '', 
			str_replace('u', '', str_replace('i', '', str_replace('y', '', $str))))));
}



function getUserProjects () {
	module_load_include('inc', 'nx', 'api/nxUser');
	$usr = nxUser::get_cur_user();
	if (!isset($usr)) return array();
	
	$q = db_select('nx_projects', 'p') -> fields('p', array())->condition('p.owner_tag', $usr->tag);
	$rows = $q -> execute ()-> fetchAllAssoc('id');
	return $rows;
}

function getSharedProjects () {
	module_load_include('inc', 'nx', 'api/nxUser');
	$usr = nxUser::get_cur_user();
	if (!isset($usr)) return array();
	
	$q = db_select('nx_projects', 'prj')->fields('prj', array());
	$q = nx_db_limit_access($q, array('prj'=>'nx_projects'), false);
	
	$rows = $q -> execute ()-> fetchAllAssoc('id');
	return $rows;
}


