<?php


class nxChar {
	public $id = -1;
	public $alias = "";
	public $world = null;
	public $owner_tag = "";
	public $access_level = 99;
	
	
	public function nxChar ($record = null) {		
		if ($record) {
			if (isset($record->id)) $this->id = $record->id;
			if (isset($record->alias)) $this->alias = $record->alias;
			if (isset($record->owner_tag)) $this->owner_tag = $record->owner_tag;
			if (isset($record->access_level)) $this->access_level = $record->access_level;		
			
			if (isset($record->world_id)) {
				module_load_include('inc', 'nx', 'api/nxWorld');
				$this->world = nxWorld::get_world_by_id($record->world_id);
			}
		}
	}
	
	
	static function get_chars ($world_id = -1) {
		$q = db_select ('nx_chars', 'c')
			-> fields ('c', array());
		if ($world_id > -1) $q -> condition ('c.world_id', $world_id);
		
		$list = array();
		if (!$rows = $q -> execute()) return $list;
		foreach ($rows as $r) {
			$list[$r->id] = new nxChar($r);
		}
		return $list;		
	}
	
}