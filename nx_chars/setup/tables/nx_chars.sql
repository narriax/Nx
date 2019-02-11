-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 11, 2019 at 04:06 AM
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
-- Table structure for table `nx_chars`
--

DROP TABLE IF EXISTS `nx_chars`;
CREATE TABLE IF NOT EXISTS `nx_chars` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `alias` varchar(16) NOT NULL,
  `wid` int(4) NOT NULL,
  `owner_tag` varchar(16) DEFAULT NULL,
  `accessid` varchar(16) DEFAULT NULL COMMENT 'access id hash',
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `alias` (`alias`),
  KEY `owner_uid` (`owner_tag`),
  KEY `world_id` (`wid`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nx_chars`
--

INSERT INTO `nx_chars` (`id`, `alias`, `wid`, `owner_tag`, `accessid`, `date_created`, `date_modified`) VALUES
(1, 'Arderian', 3, 'narriax', 'public_view', '2017-07-01 00:01:44', '2017-07-01 00:01:44');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
