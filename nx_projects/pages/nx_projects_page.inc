<?php

function nx_projects_page () {
	$t = '';
	if (count(arg()) < 2) {
		$rows_owned = getUserProjects();
		$rows_shared = getSharedProjects();
		if (count($rows_owned) < 1 && count($rows_shared) < 1) return 'No projects to show';
		
		$t .= '<b>My projects:</b><ul>';
		if (count($rows_owned) < 1)
			$t .= '<i>- none -</i>';
		foreach ($rows_owned as $rid => $row) {
			$t .= '<li>'.l($row->name, 'project/'.$rid);
			$t .= ' <font color=silver><small>('.$row->accessid.')</small></font>';
			$t .= '</li>';
		}
		$t .= '</ul><hr><b>Projects shared with me:</b><ul>';
		if (count($rows_shared) <= count($rows_owned))
			$t .= '<i>- none -</i>';
		foreach ($rows_shared as $rid => $row) {
			if (array_key_exists($rid, $rows_owned)) continue;
			$t .= '<li>'.l($row->name, 'project/'.$rid).' <font color=silver><small><i>[by '.$row->owner_tag.']</i></small></font></li>';
		}
		$t .= '</ul>';
	} else {
		$q = db_select('nx_projects', 'p') -> fields ('p', array()) -> condition('p.id', arg(1));
		$prj = $q->execute() -> fetch();
		
		if ($prj == null || empty($prj)) 
			return 'No such project found';
		
		
		$t .= '<h2>'.$prj->name.'</h2>';
		
	}
	return $t;
}
