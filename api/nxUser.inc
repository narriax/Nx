<?php

class nxUser {
	public $tag = "";
	public $uid = -1;
	public $username = "";
	
	public function nxUser ($record = null) {	
		if ($record) {
			if (isset($record->tag)) $this->tag = $record->tag;
			if (isset($record->uid)) $this->uid = $record->uid;
			if (isset($record->name)) $this->username = $record->name;
		}
	}
	
	
	function update_tag ($new_tag) {
		$this->tag = $new_tag;
		if ($this->uid < 1) return;
		
		$q = db_select ('nx_user_tags', 't')
			-> fields ('t', array())
			-> condition ('t.uid', $this->uid)
			-> range (0,1);
			
		if ($q->execute()->rowCount() > 0) {
			$q = db_update ('nx_user_tags', 't')
				-> condition ('t.uid', $this->uid)
				-> fields (array('t.tag' => $new_tag))
				-> execute();
		} else {
			$q = db_insert ('nx_user_tags')
				-> fields (array ('uid' => $this->uid, 'tag' => $new_tag))
				->execute();
		}
	}
		
	
	
	static function get_user_by_id ($uid) {
		if ($uid < 1) return null;
		$q = db_select ('users', 'u');
		$q -> leftJoin ('nx_user_tags', 't', 'u.uid=t.uid');
		$q -> condition ('u.uid', $uid)
		   -> fields ('t', array('tag'))
		   -> fields ('u', array())
		   -> range (0,1);
		if (!$record = $q -> execute() -> fetch()) {
			return null;
		}
		return new nxUser($record);
	}
	
	
	static function get_users () {
		$q = db_select ('nx_user_tags', 't');
		$q -> leftJoin ('users', 'u', 'u.uid=t.uid');
		$q -> fields ('t', array('tag'))
		   -> fields ('u', array());
		   
		$userlist = array();
		if (!$rows = $q -> execute()) return $userlist;
		foreach ($rows as $r) {
			$userlist[$r->tag] = new nxUser($r);
		}
		return $userlist;
	}
	
	static function get_user_tags () {
		$q = db_select ('nx_user_tags', 't');
		$q -> fields ('t', array());
		
		$userlist = array();
		if (!$rows = $q -> execute()) return $userlist;
		foreach ($rows as $r) {
			if (!array_key_exists($r->uid, $userlist)) $userlist[$r->uid] = array();
			$userlist[$r->uid][] = $r->tag;
		}
		return $userlist;
	}
}