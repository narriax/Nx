-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 10, 2019 at 05:22 AM
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
-- Database: `drupal7_nx`
--

-- --------------------------------------------------------

--
-- Table structure for table `nx_char_property_values`
--

DROP TABLE IF EXISTS `nx_char_property_values`;
CREATE TABLE IF NOT EXISTS `nx_char_property_values` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `chid` int(8) NOT NULL COMMENT 'character index',
  `prid` int(8) NOT NULL COMMENT 'property index',
  `value` varchar(64) NOT NULL,
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `chid` (`chid`),
  KEY `prid` (`prid`)
) ENGINE=MyISAM AUTO_INCREMENT=13 DEFAULT CHARSET=utf32;

--
-- Dumping data for table `nx_char_property_values`
--

INSERT INTO `nx_char_property_values` (`id`, `chid`, `prid`, `value`, `date_created`, `date_modified`) VALUES
(1, 1, 1, 'Arderian', '2019-02-10 04:40:27', '2019-02-10 04:40:27'),
(12, 1, 10, 'Dragonslayer', '2019-02-10 04:53:12', '2019-02-10 04:53:12'),
(11, 1, 3, 'Snowhawk', '2019-02-10 04:53:12', '2019-02-10 04:53:12'),
(10, 1, 2, 'Ard', '2019-02-10 04:53:12', '2019-02-10 04:53:12');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
