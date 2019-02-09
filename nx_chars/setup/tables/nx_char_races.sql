-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 09, 2019 at 10:24 PM
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
-- Table structure for table `nx_char_races`
--

DROP TABLE IF EXISTS `nx_char_races`;
CREATE TABLE IF NOT EXISTS `nx_char_races` (
  `id` int(8) NOT NULL AUTO_INCREMENT,
  `name` varchar(16) NOT NULL,
  `type` varchar(16) NOT NULL,
  `wid` int(4) DEFAULT NULL COMMENT 'world id',
  `parent_rid` int(8) DEFAULT NULL COMMENT 'parent id (same table)',
  `description` varchar(256) DEFAULT NULL,
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf32;

--
-- Dumping data for table `nx_char_races`
--

INSERT INTO `nx_char_races` (`id`, `name`, `type`, `wid`, `parent_rid`, `description`, `date_created`, `date_modified`) VALUES
(1, 'human', 'species', NULL, NULL, 'Homo sapiens', '2019-02-08 19:43:15', '2019-02-08 19:43:15'),
(2, 'elf', 'species', NULL, NULL, 'Homo arcanus', '2019-02-08 19:47:08', '2019-02-08 19:47:08');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
