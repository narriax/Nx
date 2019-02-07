<?php


function nx_blocks_menubar_content () {
	
	$tw = '';
	
	if (module_exists('nx_worlds')) {
		if (array_key_exists('nx_world', $_GET)) nx_var_set ('world', $_GET['nx_world']);
		
		module_load_include ('inc', 'nx_worlds', 'api/nxWorld');
		$world_tree = nxWorld::get_worlds(false);
		$world_id = nx_cur_world ();
		
		$cur_world_name = "-";
		$tw = "<ul>";
		foreach ($world_tree as $unid => $undta) {
			$tw .= "<li>".ucfirst($undta['name'])."<ul>";
			foreach ($undta['worlds'] as $wid => $world) {
				$itemclass = "";
				if ($world_id == $wid) {
					$cur_world_name = ucfirst($world->name);
					$itemclass = "selected";
				}
				$tw .= "<li class='".$itemclass."'>&nbsp;&nbsp;&#9495; <a href='?nx_world=".$wid."'>".ucfirst($world->name)."</a></li>";
			}
			$tw .= "</ul></li>";
		}
		$tw .= "</ul>";

		$tw = "<div><label>World:</label> <span>".$cur_world_name."</span></div>".$tw;
	}
	
	return "<ul><li class='worlds'>".$tw."</li></ul>";
}