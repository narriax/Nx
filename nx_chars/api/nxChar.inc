<?php


class nxChar {
	public $id = -1;
	public $alias = "";
	//public $world = null;
	public $owner_tag = "";
	public $properties = array();
	
	public function __construct  ($record = null) {		
		if ($record) {
			$prop_set = false;
			foreach ($record as $field => $value) {
				if (strpos($field, "universe_") === 0) {
					$field = substr($field, strlen("universe_"));
					$this->universe->$field = $value;
				} elseif (strpos($field, "property_") === 0) {
					if (!$prop_set) {
						$this->set_property_from_record($record);
						$prop_set = true;
					}
					continue;
				} else $this->$field = $value;
			}
			
			if (isset($record->world_id)) {
				module_load_include('inc', 'nx_worlds', 'api/nxWorld');
				$this->world = nxWorld::get_world_by_id($record->world_id);
			}
		}
	}
	
	public function get_property_values ($propid) {
		$q = db_select ('nx_char_property_values', 'cpv')
		   -> fields ('cpv', array('id', 'value'))
		   -> condition ('cpv.chid', $this->id);
		
		$list = array();
		if (!$rows = $q -> execute()) return $list;
		foreach ($rows as $r) {
			$list[$r->id] = $r->value;
		}
		return $list;
	}
	
	public function set_property ($valid, $propid, $propval) {
		if ($valid < 0) 
			$q = db_insert('nx_char_property_values') 
		       -> fields (array(
				'chid' => $this->id,
				'prid' => $propid,
				'value' => $propval,
			   )) -> execute();
		else 
			$q = db_update('nx_char_property_values')
			   -> fields (array ('value' => $propval))
			   -> condition ('id', $valid)
			   -> execute();
	} 
	
	
	private function set_property_from_record ($record) {
		if (isset($record->property_name) && isset($record->property_value)) {
			$this->set_internal_property($record->property_name, $record->property_value, $record->property_id, $record->property_value_id);
		}
	}	
	private function set_internal_property ($prop_name, $prop_value, $prop_id = null, $prop_vid = null) {
		if (!array_key_exists($prop_name, $this->properties)) {
			$this->properties[$prop_name] = array (
				'id' => $prop_id, 
				'name' => $prop_name,
				'values' => array(),
			);	
			if (isset($prop_vid)) $this->properties[$prop_name]['values'][$prop_vid] = $prop_value;
			else $this->properties[$prop_name]['values'][] = $prop_value;
		}
	}
	
	
	static function get_chars ($world_id = -1, $load_properties = array()) {
		$q = db_select ('nx_chars', 'c')
			-> fields ('c', array());
		if ($world_id > -1) $q -> condition ('c.wid', $world_id);
		$q -> leftJoin ('nx_access', 'a', 'a.accessid=c.accessid');
		$q -> addField ('a', 'name', 'accessname');
		
		if (!empty($load_properties)) {
			$q -> leftJoin ('nx_char_property_values', 'cpv', 'cpv.chid = c.id');
			$q -> leftJoin ('nx_char_properties', 'cp', 'cp.id=cpv.prid');
			$q -> addField ('cp', 'id', 'property_id');
			$q -> addField ('cp', 'name', 'property_name');
			$q -> addField ('cpv', 'id', 'property_value_id');
			$q -> addField ('cpv', 'value', 'property_value');
			
			$or = db_or()->isNull('cp.wid')->condition('cp.wid', $world_id);
			if ($load_properties[0] == '*') {
				$q->condition($or);
			} else {
				$or1 = db_or()->isNull('cp.name')->condition('cp.name', $load_properties, 'IN'); 
				$and = db_and()->condition ($or)->condition($or1);
				$q->condition($and);
			}
		}
		
		nx_db_limit_access($q, array ('c' => 'nx_chars') );
		
		$list = array();
		if (!$rows = $q -> execute()) return $list;
		foreach ($rows as $r) {
			if (!array_key_exists($r->id, $list)) $list[$r->id] = new nxChar($r);
			else $list[$r->id]->set_property_from_record($r);
		}
		return $list;		
	}
	
	static function get_char ($id, $load_properties = array()) {
		$q = db_select ('nx_chars', 'c')
		   -> fields ('c', array())
		   -> condition ('c.id', $id);
		$q -> leftJoin ('nx_access', 'a', 'a.accessid=c.accessid');
		$q -> addField ('a', 'name', 'accessname');
		
		if (!empty($load_properties)) {
			$q -> innerJoin ('nx_char_property_values', 'cpv', 'cpv.chid = c.id');
			$q -> leftJoin ('nx_char_properties', 'cp', 'cp.id=cpv.prid');
			$q -> addField ('cp', 'id', 'property_id');
			$q -> addField ('cp', 'name', 'property_name');
			$q -> addField ('cpv', 'id', 'property_value_id');
			$q -> addField ('cpv', 'value', 'property_value');
			
			if ($load_properties[0] != '*') {
				$or1 = db_or()->isNull('cp.name')->condition('cp.name', $load_properties, 'IN'); 
				$and = db_and()->condition ($or)->condition($or1);
				$q->condition($and);
			}
		}
		
		nx_db_limit_access($q, array ('c' => 'nx_chars') );
		//dpq($q);
		
		if (!$rows = $q -> execute()) return null;
		
		$char = null;
		$first = true;
		foreach ($rows as $r) {
			if ($first) {
				$char = new nxChar($r);
				$first = false;
			} else {
				$char->set_property_from_record($r);
			}
		}
		return $char;				
	}	

	static function get_all_char_properties ($world_id = -1) {
		$q = db_select ('nx_char_properties', 'cp')
		   -> fields ('cp', array());
		if ($world_id > -1) {
			$or = db_or() -> isNull('cp.wid') -> condition ('cp.wid', $world_id);
			$q -> condition ($or);
		}
		
		$list = array();
		if (!$rows = $q -> execute()) return $list;
		foreach ($rows as $r) {
			if (!array_key_exists($r->property_group, $list)) $list[$r->property_group] = array();
			$list[$r->property_group][$r->id] = $r;
		}
		return $list;			
	}
}
