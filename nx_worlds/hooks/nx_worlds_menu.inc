<?php

function nx_worlds_menu () {
	
  $items = array(); 
   
  // add a page for nx core settings
  $items['admin/config/nx/worlds'] = array(
    'title' => 'NX Worlds',
    'description' => 'Configure NX Worlds',
    'page callback' => 'drupal_get_form',
    'page arguments' => array ('nx_worlds_admin_form'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_NORMAL_ITEM,
    'weight' => -1,
	
    'file' => 'nx_worlds_admin_form.inc',
    'file path' => drupal_get_path('module', 'nx_worlds').'/pages',	
  ); 
  
  $items['worlds'] = array (
	'title' => 'Worlds',
	'description' => 'List/select worlds',
	'page callback' => 'nx_worlds_list',
	'access callback' => true,
	'type' => MENU_CALLBACK,
	'file' => 'nx_worlds_list.inc',
    'file path' => drupal_get_path('module', 'nx_worlds').'/pages',		
  );
  
	
  return $items;
}
