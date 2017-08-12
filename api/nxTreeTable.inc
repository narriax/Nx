<?php 


class nxTreeTable {
	public $structure;
	public $categories;
	public $items;
	
	public function nxTreeTable () {
		$this->structure = array('[root]' => array());
		$this->categories = array('[root]' => array('parent' => '[root]'));
		
		$this->tree = array('[root]' => array());
		$this->items = array ('[root]' => array('category' => '[root]'));
	}
	
	private function GetLineage($catname, $itemlist) {
		$lineage = array();
		$node = $catname;
		while (true) {
			$lineage[] = $node;
			if ($node == '[root]') break;
			$node = $itemlist[$node]['parent'];
		}
		return array_reverse($lineage);
	}
	
	

	// categories ===================================
	
	public function AddCategory ($catname, $parent = "[root]") {
		$this->categories[$catname] = array ('parent' => $parent, 'type' => 'leaf', 'headers' => array(), 'actions' => array(), 'dbdata' => array(), 'shown' => true);

		$parenting = $this->GetLineage ($parent, $this->categories);
		$this->categories[$catname]['lineage'] = $parenting;
		$this->categories[$parent]['type'] = 'branch';
		
		$str = '$this->structure';
		foreach ($parenting as $p) {
			$str .= '["'.$p.'"]';
		}
		$str .= '["'.$catname.'"] = array();';
		eval ($str);
	}	
	
	public function SetCategoryHeaders ($catname, $headers = array()) {
		if (!array_key_exists($catname, $this->categories)) $this->AddCategory($catname);
		$this->categories[$catname]['headers'] = $headers;
	}
	
	public function SetCategoryActions ($catname, $actions = array()) {
		if (!array_key_exists($catname, $this->categories)) $this->AddCategory($catname);
		$this->categories[$catname]['actions'] = $actions;
	}
		
	public function SetCategoryDB ($catname, $table, $parentlinkcol = '-', $childlinkcol = 'id') {
		if (!array_key_exists($catname, $this->categories)) $this->AddCategory($catname);
		$this->categories[$catname]['dbdata'] = array (
			'table' => $table,
			'parentlink' => $parentlinkcol,
			'childlink' => $childlinkcol,
		);
	}
	
	// items ===================================
	public function AddItem ($category, $itemname, $parentItem = '[root]') {
		if (!array_key_exists($category, $this->categories)) $this->AddCategory($category);
		if (!array_key_exists($parentItem, $this->items)) $this->AddItem($this->categories[$category]['parent'], $parentItem);
		
		$this->items[$itemname] = array ('parent' => $parentItem, 'category' => $category, 'type' => 'leaf');
		
		$parenting = $this->GetLineage ($parentItem, $this->items);
		$this->items[$parentItem]['type'] = 'branch';
		$this->items[$itemname]['lineage'] = $parenting;
	
		$str = '$this->items';
		foreach ($parenting as $p) {
			$str .= '["'.$p.'"]';
		}
		$str .= '["'.$itemname.'"] = array();';
		eval ($str);	
	}
	
	public function FetchItems() {
		
		$toptables = array();
		$queries = array();

		// top level tables
		foreach ($this->structure['[root]'] as $c => $children) {
			$category = $this->categories[$c];
			if (!array_key_exists('table', $category['dbdata']) || empty($category['dbdata']['table'])) {
				dvm('ERROR (FetchItems): category ['.$c.'] has no associated DB data, items cannot be fetched');
				continue;					
			}
			$queries[$c] = db_select($category['dbdata']['table'], $c)->fields($c, array());
			$queries[$c] = nx_db_limit_access($queries[$c], $c);
		}

		// all other tables
		foreach ($this->categories as $c => $category) {
			if ($c == '[root]' || $category['parent'] == '[root]') continue;

			if (!array_key_exists('table', $category['dbdata']) || empty($category['dbdata']['table']) ||
				!array_key_exists('parentlink', $category['dbdata']) || empty($category['dbdata']['parentlink']) ||	
				!array_key_exists('childlink', $category['dbdata']) || empty($category['dbdata']['childlink'])) {
				
				dvm('ERROR (FetchItems): category ['.$c.'] has no associated DB data, items cannot be fetched');
				continue;
			}

			$topparent = $category['lineage'][1];
			//echo "$c: ".implode($category['lineage']." || " + $topparent);
			if (!array_key_exists($topparent, $queries)) {
				dvm('ERROR (FetchItems): unable to find query for category ['.$c.']');
				continue;				
			}
			
			$parentlink = $c.'.'.$category['dbdata']['parentlink'];
			$childlink = $c.'.'.$category['dbdata']['childlink'];
			$queries[$topparent] -> join($category['dbdata']['table'], $c, $childlink.'='.$parentlink);
			$queries[$topparent] -> fields ($c, array());
			$queries[$topparent] = nx_db_limit_access($queries[$topparent], $c);
		}
		
		
		// run queries
		$results = array();
		foreach ($queries as $c => $q) {
			dpq($q);
			
			if ($r = $q->execute()->fetchAll()) {
				$results[$c] = $r;
			}
		}
		dpm($resutls);
		
		
	}
	
	
	
}



