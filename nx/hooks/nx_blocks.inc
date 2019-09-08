<?php


function nx_block_info() {
	$blocks['nx_menubar'] = array (
		'info' => t('NX Menu bar'),
		'cache' => DRUPAL_NO_CACHE,
	);
	return $blocks;	
}

function nx_block_view($delta = '') {
	$block = array();
	switch ($delta) {
		case 'nx_menubar':
			module_load_include('inc', 'nx', 'blocks/nx_blocks_menubar');
			$block['subject'] = '';
			$block['content'] = array (
				//'#theme' => 'feed_icon',
				//'#url' => 'rss.xml',
				'#title' => t('NX Menu bar'),
				'#markup' => nx_blocks_menubar_content(),
				'#attached' => array (
					'css' => array(
						drupal_get_path('module', 'nx') . '/blocks/nx_blocks_menubar.css',
					),
				//	'js' => array(
				//		drupal_get_path('module', 'mymodule') . '/js/mymodule.js',
				//	),
				),
			);
		break;
	}
	return $block;	
}