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
	
	
	static function get_users () {
		$q = db_select ('nx_user_tags', 't');
		$q -> leftJoin ('users', 'u', 'u.uid=t.uid');
		$q -> fields ('t', array())
		   -> fields ('u', array('name'));
		   
		$userlist = array();
		if (!$rows = $q -> execute()) return $userlist;
		foreach ($rows as $r) {
			$userlist[$r->tag] = new nxUser($r);
		}
		return $userlist;
	}
	
}