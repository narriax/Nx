<?php

function nx_chars_menu () {
	
  $items['chars'] = array(
    'title' => 'Characters',
    'description' => 'Browse and edit, add and remove characters',
    'type' => MENU_NORMAL_ITEM,
		
    'page callback' => 'nx_chars_list',
    'access callback' => true,
    'file' => 'nx_chars_list.inc',
    'file path' => drupal_get_path('module', 'nx_chars').'/pages',
  );
  
  $items['char'] = array(
    'title' => 'Character',
    'description' => 'View and edit a character',
    'type' => MENU_CALLBACK,
		
    'page callback' => 'nx_char_view',
    'access callback' => true,
	'file' => 'nx_char_view.inc',
    'file path' => drupal_get_path('module', 'nx_chars').'/pages',
  );
	
  return $items;
}
