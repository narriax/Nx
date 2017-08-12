<?php

function nx_menu () {
	
  $items = array(); 
   
  // add config category for all things NX
  $items['admin/config/nx'] = array(
    'title' => 'NX Modules',
    'description' => 'Configure NX modules',
    
    'position' => 'left',
    'weight' => -100,
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('administer site configuration'),
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
  );
  
  // add a page for nx core settings
  $items['admin/config/nx/core'] = array(
    'title' => 'NX framework',
    'description' => 'Configure NX core framework',
    'page callback' => 'drupal_get_form',
    'page arguments' => array ('nx_admin_form'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_NORMAL_ITEM,
    'weight' => -1,
	
    'file' => 'nx_admin_form.inc',
    'file path' => drupal_get_path('module', 'nx').'/pages',	
  ); 	
  
  // add a page for module tables udpates
  $items['admin/config/nx/core/update'] = array(
    'title' => 'NX updates',
    'description' => 'Configure NX core framework',
    'page callback' => 'drupal_get_form',
    'page arguments' => array ('nx_update_form'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_NORMAL_ITEM,
    'weight' => -1,
	
    'file' => 'nx_update_form.inc',
    'file path' => drupal_get_path('module', 'nx').'/pages',	
  ); 	
  
  
  // add a tab to the people admin list for nx tags
  $items['admin/people/tags'] = array(
    'title' => 'NX Tags',
    'callback' => 'nx_admin_tags_form', 
    'page callback' => 'drupal_get_form',
    'page arguments' => array ('nx_admin_tags_form'),
    'file' => 'nx_admin_tags_form.inc',
    'file path' => drupal_get_path('module', 'nx').'/pages',		
    'access arguments' => array('administer site configuration'),
    'type' => MENU_LOCAL_TASK,
  );  
	
	
	
  return $items;
}
