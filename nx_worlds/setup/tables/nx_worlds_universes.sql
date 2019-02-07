-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Aug 12, 2017 at 12:35 AM
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
-- Table structure for table `nx_worlds_universes`
--

CREATE TABLE IF NOT EXISTS `nx_worlds_universes` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `name` varchar(16) NOT NULL,
  `owner_tag` varchar(16) DEFAULT NULL,
  `enabled` tinyint(1) NOT NULL DEFAULT '1',
  `accessid` varchar(16) NOT NULL DEFAULT '',
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `desc` text NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  KEY `owner_uid` (`owner_tag`,`accessid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `nx_worlds_universes`
--

INSERT INTO `nx_worlds_universes` (`id`, `name`, `owner_tag`, `enabled`, `accessid`, `date_created`, `date_modified`, `desc`) VALUES
(1, 'reality', NULL, 1, '', '2017-06-30 19:47:13', '2017-06-30 19:47:13', ''),
(2, 'gaming', NULL, 1, '', '2017-06-30 19:49:18', '2017-06-30 19:49:18', ''),
(3, 'creative', NULL, 1, '', '2017-06-30 19:48:53', '2017-06-30 19:48:53', '');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
