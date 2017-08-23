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
		
	public function SetCategoryDB ($catname, $table, $idcol = 'id', $parentlinkcol = '-', $childlinkcol = 'id') {
		if (!array_key_exists($catname, $this->categories)) $this->AddCategory($catname);
		$this->categories[$catname]['dbdata'] = array (
			'table' => $table,
			'idcol' => $idcol,
			'parentlink' => $parentlinkcol,
			'childlink' => $childlinkcol,
		);
	}
	
	// items ===================================
	public function AddItem ($category, $itemname, $itemdata = array(), $parentItem = '[root]', $overwrite = false) {
		if (array_key_exists($parentItem, $this->items))
		if (!array_key_exists($category, $this->categories)) $this->AddCategory($category);
		if (!array_key_exists($parentItem, $this->items)) $this->AddItem($this->categories[$category]['parent'], $parentItem);
		
		$this->items[$itemname] = array ('parent' => $parentItem, 'category' => $category, 'type' => 'leaf');
		
		$parenting = $this->GetLineage ($parentItem, $this->items);
		$this->items[$parentItem]['type'] = 'branch';
		$this->items[$itemname]['lineage'] = $parenting;
		$this->items[$itemname]['data'] = $itemdata;
	
		$str = '$this->tree';
		foreach ($parenting as $p) {
			$str .= '["'.$p.'"]';
		}
		$str .= '["'.$itemname.'"] = array();';
		eval ($str);	
	}
	
	
	public function FetchItems() {
		
		$toptables = array();
		$queries = array();
		$table_cols = nx_db_get_cols();
		
		// top level tables
		foreach ($this->structure['[root]'] as $c => $children) {
			$category = $this->categories[$c];
			if (!array_key_exists('table', $category['dbdata']) || empty($category['dbdata']['table'])) {
				dvm('ERROR (FetchItems): category ['.$c.'] has no associated DB data, items cannot be fetched');
				continue;					
			}
			$queries[$c] = db_select($category['dbdata']['table'], $c);
			if (array_key_exists($category['dbdata']['table'], $table_cols)) {
				foreach ($table_cols[$category['dbdata']['table']] as $col => $coltype) {
					$queries[$c]->addField($c, $col, $c.'__'.$col);
				}
			} else {
				dvm('ERROR (FetchItems): category ['.$c.'] had no columns fetched');
				$queries[$c]->fields($c, array());
			}
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
			
			$my_link_to_parent = $c.'.'.$category['dbdata']['parentlink'];
			$parent_link_to_child = $topparent.'.'.$this->categories[$topparent]['dbdata']['childlink'];
			$queries[$topparent] -> join($category['dbdata']['table'], $c, $my_link_to_parent.'='.$parent_link_to_child);
			
			if (array_key_exists($category['dbdata']['table'], $table_cols)) {
				foreach ($table_cols[$category['dbdata']['table']] as $col => $coltype) {
					$queries[$topparent]->addField($c, $col, $c.'__'.$col);
				}
			} else {
				dvm('ERROR (FetchItems): category ['.$c.'] had no columns fetched');
				$queries[$topparent]->fields($c, array());
			}
			$queries[$topparent] = nx_db_limit_access($queries[$topparent], $c);
		}
		
		
		// run queries and add items
		foreach ($queries as $q) {			
			if ($results = $q->execute()->fetchAll()) {
				foreach ($results as $ix => $r) {
					$row = array();
								
					foreach ($r as $field => $value) {
						$category = explode('__', $field)[0];
						$col = explode('__', $field)[1];
					
						if (!array_key_exists($category, $row)) $row[$category] = array();
						$row[$category][$col] = $value;
					}
					
					$this->FetchItems_Helper ($row, $this->structure['[root]']);
				}		
			}
		}		
	}
	
	
	private function FetchItems_Helper ($row, $category_parent, $parent_id = '[root]') {
		foreach ($category_parent as $cat => $contents) {
			if (!array_key_exists($cat, $row)) continue;
			$idcol = $this->categories[$cat]['dbdata']['idcol'];
			$id = $cat.'_'.$row[$cat][$idcol];					
			$this->AddItem ($cat, $id, $row[$cat], $parent_id);
			
			$this->FetchItems_Helper ($row, $contents, $id);
		}
	}
	
	
	public function LinearizeCategoryStructure() {
		$line = array();
		$this->LinearizeCategoryStructure_Helper ($this->structure['[root]'], $line);
		return $line;
	}
	private function LinearizeCategoryStructure_Helper ($cattyparent, &$line) {
		if (empty($cattyparent)) return;
		$first = array_keys($cattyparent)[0];
		$line[] = $first;
		$this->LinearizeCategoryStructure_Helper ($cattyparent[$first], $line);
	}
	
	
	public function CreateTableselect ($title) {
			
		$table = array (
			'#type' => 'tableselect',
			'#title' => $title,
			'#header' => array(),
			'#options' => array(),
		);
		
		$line = $this->LinearizeCategoryStructure();
		foreach ($line as $cat) {
			$table['#header'][$cat] = $cat;
		}
		if (count($this->items) > 1) {
			foreach ($this->items as $i => $item) {
				if ($i == '[root]') continue;
				foreach ($item['data'] as $field => $value) {
					if ($field == 'id' || $field == 'name') continue;
					if (array_key_exists('dbdata', $this->categories[$item['category']])) {
						if ($field == $this->categories[$item['category']]['dbdata']['parentlink']) continue;
						if ($field == $this->categories[$item['category']]['dbdata']['childlink']) continue;
					}
					$table['#header'][$field] = $field;
					break;
				}
			}
		}
		$table['#header']['actions'] = 'actions';
		foreach ($table['#header'] as $col => $name) $table['#header'][$col] = str_replace('_', ' ', $name);
		
		return $table;
	}
	
	
	
	
}



