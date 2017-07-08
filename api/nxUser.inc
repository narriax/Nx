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
			$q = db_update ('nx_user_tags')
				-> condition ('uid', $this->uid)
				-> fields (array(
					'tag' => $new_tag,
					'date_modified' => date('Y-m-d G:i:s'),
				))
				-> execute();
		} else {
			$q = db_insert ('nx_user_tags')
				-> fields (array ('uid' => $this->uid, 'tag' => $new_tag))
				->execute();
		}
	}
		
		
	// ===============================================================================
	//  static user fetchers
	// ===============================================================================
	
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
		$q = db_select ('users', 'u');
		$q -> leftJoin ('nx_user_tags', 't', 'u.uid=t.uid');		
		$q -> fields ('t', array('tag'))
		   -> fields ('u', array());
		   
		$userlist = array();
		if (!$rows = $q -> execute()) return $userlist;
		foreach ($rows as $r) {
			if (!empty($r->tag)) $userlist[$r->tag] = new nxUser($r);
			else $userlist['_uid_'.$r->uid] = new nxUser($r);
		}
		return $userlist;
	}
	
	
	// ===============================================================================
	// 	static bulk tags
	// ===============================================================================
	
	static function get_tag_info ($tag_list = array ()) {
		$q = db_select ('nx_user_tags', 't') -> fields ('t', array());
		if (!empty($tag_list)) $q -> condition ('t.tag', $tag_list, 'IN') -> range (0, count($tag_list));
		
		$taglist = array ();
		if (!$rows = $q -> execute()) return $taglist;
		
		foreach ($rows as $r) {
			$taglist[$r->tag] = $r;
		}
		return $taglist;
	}
	
	
	static function get_user_tags ($list_as_array = true) {
		$q = db_select ('nx_user_tags', 't');
		$q -> fields ('t', array('uid', 'tag'));
		
		$userlist = array();
		if (!$rows = $q -> execute()) return $userlist;
		foreach ($rows as $r) {
			if (!array_key_exists($r->uid, $userlist)) $userlist[$r->uid] = array();
			$userlist[$r->uid][] = $r->tag;
		}
		if (!$list_as_array) {
			foreach ($userlist as $uid => $taglist) {
				$userlist[$uid] = implode (', ', $userlist[$uid]);
			}
		}
		return $userlist;
	}
	
	
	static function delete_tags ($list) {
		if (empty($list)) return;
		$q = db_delete('nx_user_tags')
		   -> condition ('tag', $list, 'IN')
		   -> execute();
		
	}
}