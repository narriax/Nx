<?php

function nx_projects_menu () {
	
	$items = array();

    $items['admin/config/nx'] = array( 
        //this section is for  create a  section
        'title' => t('NX') ,//this section will create  under admin->config
        'description' => t('NX Config') ,
        'weight' => -100,
        'page callback' => 'system_admin_menu_block_page',
        'access arguments' => array('access administration pages'),
        'file' => 'system.admin.inc',
        'file path' => drupal_get_path('module', 'system'),
        'position' => 'left',
	);  
	
	$items['admin/config/nx/projects'] = array(
        //this should be the path of your admin listing page 
        'title' => 'Projects',
        'description' => 'Manage subsites',
        //'page callback' => 'nx_section_config_form',
		'page callback' => 'drupal_get_form',
        'page arguments' => array('nx_projects_admin_form'),
        'access arguments' => array('NX admin projects'),
        'file' => '/pages/nx_projects_admin_form.inc',
        'weight' => -10,
    );
	$q = db_select('nx_projects', 'p') -> fields('p', array());
	$rows = $q -> execute ()-> fetchAllAssoc('id');
	foreach ($rows as $rid => $row) {
		$items['project'] = array (
			'page callback' => 'nx_projects_page',
			'access callback' => true,
			'file' => '/pages/nx_projects_page.inc',
		);
	}
	
	return $items;
}
