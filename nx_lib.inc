<?php


function nx_var ($name = "") {
	if (empty($name)) return null;
	if (!array_key_exists('nx', $_SESSION)) return null;
	if (!array_key_exists($name, $_SESSION['nx'])) return null;
	return $_SESSION['nx'][$name];
}

function nx_var_set ($name = "", $value = false) {
	if (empty($name)) return; 
	if (!array_key_exists('nx', $_SESSION)) $_SESSION['nx'] = array();
	$_SESSION['nx'][$name] = $value;
}