<?php


function nx_cur_world () {
	if (!nx_var ('world')) {
		dvm ('redirect to select world');
		return -1;
	} else return nx_var ('world');
}