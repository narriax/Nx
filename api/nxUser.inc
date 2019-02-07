<?php

class nxUser {
	public $tag = "";
	public $uid = -1;
	public $username = "";
	public $namef = "";
	public $namel = "";
	
	
	public function __construct ($record = null) {	
		if ($record) {
			foreach ($record as $field => $value) {
				if ($field == 'name') $field = 'username';
				$this->$field = $value;
			}
			if ($this->uid == 1) {
				$this->roles[0] = 'god';
				$this->roles[3] = 'administrator';
			}
		}
	}
	
	public function get_fullname () {
		return trim($this->namef.' '.$this->namel);
	}
	
	
	function update_setting ($setting, $value) {
		if ($this->uid < 1) return;
		
		// find this setting
		$q = db_select ('nx_user_settings', 'us')
		   -> fields ('us', array())
		   -> condition ('us.name', $setting)
		   -> range (0, 1);
		if (!$s = $q->execute()->fetch()) {
			dvm ('unknown setting ['.$setting.']');
			return;
		} elseif (!isset($s->sid)|| $s->sid < 1) {
			dvm ('unknown setting ['.$setting.']');
			return;			
		}
		
		// now find existing value (if any)
		$q = db_select ('nx_user_setting_values', 'usv');
		$q -> fields ('usv', array('value'))
		   -> range (0,1);				
		
		$and = db_and();
		$and -> condition ('usv.uid', $this->uid);
		$and -> condition ('usv.sid', $s->sid);
		$q -> condition ($and);
		
		
		if ($r = $q->execute()->fetch()) {
			if ($r->value != $value) {
				$and = db_and();
				$and -> condition ('uid', $this->uid);
				$and -> condition ('sid', $s->sid);				
				
				$q = db_update ('nx_user_setting_values')
					-> condition ($andd)
					-> fields (array(
						'value' => $value,
						'date_modified' => date('Y-m-d G:i:s'),
					))
					-> execute();				
			}
		} else {
			$q = db_insert ('nx_user_setting_values')
				-> fields (array ('uid' => $this->uid, 'sid' => $s->sid, 'value' => $value))
				->execute();			
		}
		
	}
	
	function update_name ($namef, $namel) {
		$this->namef = $namef;
		$this->namel = $namel;
		$this->update_setting('namef', $namef);
		$this->update_setting('namel', $namel);
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
	
	static function get_cur_user () {
		global $user, $cur_user;
		if (!isset($cur_user)) {
			if ($user->uid < 1) return null;
			$cur_user = nxUser::get_user_by_id($user->uid);
		}
		return $cur_user;
	}
	
	static function get_user_by_id ($uid, $fetch_settings = array ('namef', 'namel')) {
		if ($uid < 1) return null;
		
		// write query as raw sql, because drupal db framework does not support row->column transposition we do for $fetch_settings
		$q_fields = 'u.*, t.tag AS tag';
		$q_tables = '{users} u '.
					'LEFT OUTER JOIN {nx_user_tags} t ON t.uid=u.uid ';
		$q_conditions = 'u.uid='.$uid;
		$q_tail = '';
		
		if (!empty($fetch_settings)) {
			foreach ($fetch_settings as $s) {
				$q_fields .= ", MAX(CASE when us.name = '".$s."' THEN usv.value END) AS '".$s."' ";
			}
			$q_tables .= 'LEFT OUTER JOIN {nx_user_setting_values} usv ON usv.uid=u.uid ' ;
			$q_tables .= 'LEFT OUTER JOIN {nx_user_settings} us ON us.sid=usv.sid ' ;
			$q_tail .= ' GROUP BY u.uid';
		}
		
		$q = db_query('SELECT '.$q_fields.' FROM '.$q_tables.' WHERE '.$q_conditions.' '.$q_tail.' LIMIT 1');	
	
		if (!$record = $q -> fetch()) {
			return null;
		}
		
		$q = db_select ('users_roles', 'ur');
		$q -> join ('role', 'r', 'r.rid = ur.rid');
		$q -> fields ('r', array('rid', 'name'))
		   -> condition ('ur.uid', $record->uid);
		$record->roles = $q->execute()->fetchAllKeyed(0, 1);
					
		return new nxUser($record);
	}
	

	static function get_users ($fetch_settings = array ('namef', 'namel')) {
	
		// write query as raw sql, because drupal db framework does not support row->column transposition we do for $fetch_settings
		$q_fields = 'u.*, t.tag AS tag';
		$q_tables = '{users} u LEFT OUTER JOIN {nx_user_tags} t ON t.uid=u.uid ';
		$q_tail = '';
		
		if (!empty($fetch_settings)) {
			foreach ($fetch_settings as $s) {
				$q_fields .= ", MAX(CASE when us.name = '".$s."' THEN usv.value END) AS '".$s."'";
			}
			$q_tables .= 'LEFT OUTER JOIN {nx_user_setting_values} usv ON usv.uid=u.uid ' ;
			$q_tables .= 'LEFT OUTER JOIN {nx_user_settings} us ON us.sid=usv.sid ' ;
			$q_tail .= ' GROUP BY u.uid';
		}
		
		$q = db_query('SELECT '.$q_fields.' FROM '.$q_tables.$q_tail);	   
		   
		$userlist = array();
		if (!$rows = $q -> fetchAll()) return $userlist;
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