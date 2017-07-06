<?php

class nxWorld {
	public $id = -1;
	public $name = "";
	public $universe = null;
	public $owner_tag = "";
	public $access_level = 99;
	
	public function nxWorld ($world_id = -1, $record = null) {	
		$this->universe = new stdClass();
		$this->universe->id = -1;
		$this->universe->name = "";
	
		if ($record) {
			if (isset($record->id)) $this->id = $record->id;
			if (isset($record->name)) $this->name = $record->name;
			if (isset($record->universe_id)) $this->universe->id = $record->universe_id;
			if (isset($record->universe_name)) $this->universe->name = $record->universe_name;
			if (isset($record->owner_tag)) $this->owner_tag = $record->owner_tag;
			if (isset($record->access_level)) $this->access_level = $record->access_level;
		} elseif ($world_id > -1) {
			$world = nxWorld::get_world_by_id ($world_id);
			foreach ($world as $property => $value) {
				$this->$property = $value;
			}
		}
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
	static function get_worlds () {
		$q = db_select ('nx_worlds', 'w');
		$q -> leftJoin ('nx_worlds_universes', 'wu', 'wu.id=w.universe_id');
		$q -> fields ('w', array())
		   -> addField ('wu', 'name', 'universe_name');
		   
		$list = array();
		if (!$rows = $q -> execute()) return $list;
		foreach ($rows as $r) {
			$list[$r->id] = new nxWorld(-1, $r);
		}
		return $list;
	}
	
	
	
}