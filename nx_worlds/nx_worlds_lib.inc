<?php


function nx_cur_world () {
	if (!nx_var ('world')) return -1;
	else return nx_var ('world');
}