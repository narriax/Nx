<?php

function nx_menu () {
	
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
	
  return $items;
}
