<?php

class nxWorld {
	public $id = -1;
	public $name = "";
	public $universe = null;
	public $owner_tag = null;
	
	public function nxWorld ($record = null) {	
		$this->universe = new stdClass();
		$this->universe->id = -1;
		$this->universe->name = "";
	
		if ($record) {
			if (isset($record->id)) $this->id = $record->id;
			if (isset($record->name)) $this->name = $record->name;
			if (isset($record->universe_id)) $this->universe->id = $record->universe_id;
			if (isset($record->universe_name)) $this->universe->name = $record->universe_name;
			if (isset($record->owner_tag)) $this->owner_tag = $record->owner_tag;
		}
	}	
	
	static function get_worlds () {
		$q = db_select ('nx_worlds', 'w');
		$q -> leftJoin ('nx_worlds_universes', 'wu', 'wu.id=w.universe_id');
		$q -> fields ('w', array())
		   -> addField ('wu', 'name', 'universe_name');
		   
		$list = array();
		if (!$rows = $q -> execute()) return $list;
		foreach ($rows as $r) {
			$list[$r->id] = new nxWorld($r);
		}
		return $list;
	}	
}