<?php

function nx_projects_block_info () {
	$blocks = array();
	$blocks['nx_projects'] = array(
		'info' => t('NX Projects Menu'),
	);  
	return $blocks;
}
function nx_projects_block_view($delta='') {
//  module_load_include('inc', 'nx', 'api/nxUser');
//  $usr = nxUser::get_cur_user();
//  if ($usr == null) return;
	
  $block = array();
  switch($delta) {
    case 'nx_projects' :
	  $block['content'] = array();
	  $block['content']['title'] = array ('#markup' => '<b>'.l('Projects:', 'project').'</b>');
	  
	  	$q = db_select('nx_projects', 'prj') -> fields('prj', array()) -> condition ('prj.barpos', -1, '>');
		$q = nx_db_limit_access($q, array('prj' => 'nx_projects'));
		if (!isset($q)) return array();
		
		$rows = $q -> execute ()-> fetchAllAssoc('id');
		foreach ($rows as $rid => $row) {
			$block['content']['prj_'.$rid] = array ('#markup' => ' '.l($rid, 'project/'.$rid));
		}
	
      break;
  }
  return $block;
}
