-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Aug 12, 2017 at 12:36 AM
-- Server version: 5.6.17
-- PHP Version: 5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `colony`
--

-- --------------------------------------------------------

--
-- Table structure for table `nx_access`
--

CREATE TABLE IF NOT EXISTS `nx_access` (
  `accessid` varchar(16) NOT NULL COMMENT 'item id hash',
  `editaccess` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'false=view, true=edit',
  `utag` int(11) NOT NULL COMMENT 'user tag',
  `alid` int(11) NOT NULL COMMENT 'access level id',
  `whiteusers` varchar(512) NOT NULL DEFAULT '' COMMENT 'whitelist for user tags',
  `blackusers` varchar(512) NOT NULL DEFAULT '' COMMENT 'blacklist for user tags',
  `whitegroups` varchar(512) NOT NULL DEFAULT '' COMMENT 'whitelist for group tags',
  `blackgroups` varchar(512) NOT NULL DEFAULT '' COMMENT 'blacklist for group tags',
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`accessid`),
  KEY `utag` (`utag`,`alid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
