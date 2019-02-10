<?php


class nxChar {
	public $id = -1;
	public $alias = "";
	public $world = null;
	public $owner_tag = "";
	
	
	public function __construct  ($record = null) {		
		if ($record) {
			foreach ($record as $field => $value) {
				if (strpos($field, "universe_") === 0) {
					$field = substr($field, strlen("universe_"));
					$this->universe->$field = $value;
				} else $this->$field = $value;
			}
			
			if (isset($record->world_id)) {
				module_load_include('inc', 'nx_worlds', 'api/nxWorld');
				$this->world = nxWorld::get_world_by_id($record->world_id);
			}
		}
	}
	
	
	static function get_chars ($world_id = -1) {
		$q = db_select ('nx_chars', 'c')
			-> fields ('c', array());
		if ($world_id > -1) $q -> condition ('c.world_id', $world_id);
		$q -> leftJoin ('nx_access', 'a', 'a.accessid=c.accessid');
		$q -> addField ('a', 'name', 'accessname');
		
		nx_db_limit_access($q, array ('c' => 'nx_chars') );
		
		$list = array();
		if (!$rows = $q -> execute()) return $list;
		foreach ($rows as $r) {
			$list[$r->id] = new nxChar($r);
		}
		return $list;		
	}
	
}