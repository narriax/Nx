<?php

class nxWorld {
	public $id = -1;
	public $name = "";
	public $universe = null;
	public $owner_tag = "";
	
	public function __construct  ($world_id = -1, $record = null) {	
		$this->universe = new stdClass();
		$this->universe->id = -1;
		$this->universe->name = "";

		if ($record) {
			//dpm($record, 'record='.$record->name);
			foreach ($record as $field => $value) {
				if (strpos($field, "universe_") === 0) {
					$field = substr($field, strlen("universe_"));
					$this->universe->$field = $value;
				} else $this->$field = $value;
			}
		} elseif ($world_id > -1) {
			$world = nxWorld::get_world_by_id ($world_id);
			foreach ($world as $property => $value) {
				$this->$property = $value;
			}
		}
	}	
	
	public function delete () {
		dvm ('TODO: delete world '.$this->id);
	}
	
	// =================================================================
	static function get_world_by_id ($world_id) {
		if ($world_id < 0) return null;
		
		$q = db_select ('nx_worlds', 'w');
		$q -> leftJoin ('nx_worlds_universes', 'wu', 'wu.id=w.universe_id');
		$q -> condition ('w.id', $world_id)
		   -> fields ('w', array())
		   -> addField ('wu', 'name', 'universe_name');		
		   
		if (!$record = $q->execute()->fetch()) return null;
		return new nxWorld(-1, $record);
	}
	
	// =================================================================
	private static function get_world_from_record ($record = null) {
		if ($record == null) return null;
		return new nxWorld(-1, $record);
	}
	
	// =================================================================
	
	static function get_worlds ($index_by_world = true) {
		$q = db_select ('nx_worlds', 'w');
		$q -> leftJoin ('nx_worlds_universes', 'wu', 'wu.id=w.universe_id');
		$q -> fields ('w', array())
		   -> addField ('wu', 'name', 'universe_name');
		$q -> addField ('wu', 'owner_tag', 'universe_owner_tag');
		$q -> addField ('wu', 'accessid', 'universe_accessid');
		
		$q -> leftJoin ('nx_access', 'a1', 'a1.accessid=w.accessid');
		$q -> addField ('a1', 'name', 'accessname');

		$q -> leftJoin ('nx_access', 'a2', 'a2.accessid=wu.accessid');
		$q -> addField ('a2', 'name', 'universe_accessname');

		nx_db_limit_access($q, array ('w' => 'nx_worlds', 'wu' => 'nx_worlds_universes') );
		   
		$list = array();
		if (!$rows = $q -> execute()) return $list;
		
		foreach ($rows as $r) {
			if ($index_by_world) {
				$list[$r->id] = new nxWorld(-1, $r);
			} else {
				if (!array_key_exists($r->universe_id, $list)) {
					$list[$r->universe_id] = array ('name' => $r->universe_name, 'worlds' => array());
					$list[$r->universe_id]['owner_tag'] = $r->universe_owner_tag;
					$list[$r->universe_id]['acessid'] = $r->universe_accessid;
					$list[$r->universe_id]['accessname'] = $r->universe_accessname;
				}
				$list[$r->universe_id]['worlds'][$r->id] = new nxWorld(-1, $r);
			}
		}
		return $list;
	}
	
	static function get_universes () {
		$q = db_select ('nx_worlds_universes', 'wu')
			-> fields ('wu', array('id', 'name'))
			-> orderBy ('wu.name');
		if (!$rows = $q -> execute()) return array();
		return $rows -> fetchAllKeyed(0,1);
	}
	

	
	
}