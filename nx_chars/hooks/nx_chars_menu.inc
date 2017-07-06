<?php

function nx_chars_menu () {
	
  $items['chars'] = array(
    'title' => 'Characters',
    'description' => 'Browse and edit, add and remove characters',
    'type' => MENU_NORMAL_ITEM,
		
    'page callback' => 'nx_chars_list',
	//'page arguments' => array ('nx_admin_form'),
    'access arguments' => array('administer site configuration'),
    'file' => 'nx_chars_list.inc',
    'file path' => drupal_get_path('module', 'nx_chars').'/pages',
  );
  
	
  return $items;
}
