-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 09, 2019 at 10:25 PM
-- Server version: 5.7.24
-- PHP Version: 7.2.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `nx_drupal7`
--

-- --------------------------------------------------------

--
-- Table structure for table `nx_worlds_universes`
--

DROP TABLE IF EXISTS `nx_worlds_universes`;
CREATE TABLE IF NOT EXISTS `nx_worlds_universes` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `name` varchar(16) NOT NULL,
  `enabled` tinyint(1) NOT NULL DEFAULT '1',
  `owner_tag` varchar(16) DEFAULT NULL,
  `accessid` varchar(16) DEFAULT NULL COMMENT 'access id hash',
  `desc` text NOT NULL,
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  KEY `owner_uid` (`owner_tag`,`accessid`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nx_worlds_universes`
--

INSERT INTO `nx_worlds_universes` (`id`, `name`, `enabled`, `owner_tag`, `accessid`, `desc`, `date_created`, `date_modified`) VALUES
(1, 'reality', 1, NULL, NULL, '', '2017-06-30 23:47:13', '2017-06-30 23:47:13'),
(2, 'gaming', 1, NULL, NULL, '', '2017-06-30 23:48:53', '2017-06-30 23:48:53'),
(3, 'creative', 1, NULL, NULL, '', '2017-06-30 23:49:18', '2017-06-30 23:49:18');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
