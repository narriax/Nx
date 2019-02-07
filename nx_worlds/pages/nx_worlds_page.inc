<?php

function nx_worlds_page () {
	$t = '';
	
	$world_id = nx_cur_world ();
	if ($world_id < 0) $t .= '<div class="messages action">Please select a world to continue</div>';
	
	module_load_include ('inc', 'nx_worlds', 'api/nxWorld');
	$world_tree = nxWorld::get_worlds(false, true);
	dpm($world_tree);
	
	$t .= "<table><tr><th>Universe</th><th>World</th><th>Description</th></tr>";
	foreach ($world_tree as $unid => $undta) {	
		$firstrow = true;
		foreach ($undta['worlds'] as $wid => $world) {
			
			
			
			if ($world_id == $wid) $itemclass = "selected";
			else $itemclass = "";
			
			$t .= "<tr class='".$itemclass."'>";
			if ($firstrow) {
				$t .= "<td rowspan=".count($undta['worlds'])."><b>".ucfirst($undta['name']).'</b>';
				if ($undta['owner_tag'] != null) {
					$t .= " (".$undta['owner_tag'];
					if ($undta['accessname'] != null) $t .= ": ".$undta['accessname'];
					$t .= ")";
				}
				$t .= "</td>";
				$firstrow = false;
			}
			
			$t .= "<td><a href='?nx_world=".$wid."'>".ucfirst($world->name)."</a>";
			if ($world->owner_tag != null) {
				$t .= " (".$world->owner_tag;
				if ($world->accessname != null) $t .= ": ".$world->accessname;
				$t .= ")";
			}
			$t .= "</td><td>".$world->desc."</td>";
			$t .= "</tr>";
		}
	}
	$t .= "</table>";

	return $t;
}