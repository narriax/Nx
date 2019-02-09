-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 09, 2019 at 10:42 PM
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
-- Table structure for table `nx_maps_places`
--

DROP TABLE IF EXISTS `nx_maps_places`;
CREATE TABLE IF NOT EXISTS `nx_maps_places` (
  `id` int(8) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL,
  `type` varchar(16) NOT NULL,
  `wid` int(4) NOT NULL COMMENT 'world index',
  `parent_pid` int(8) DEFAULT NULL COMMENT 'parent place id',
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `wid` (`wid`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=utf32;

--
-- Dumping data for table `nx_maps_places`
--

INSERT INTO `nx_maps_places` (`id`, `name`, `type`, `wid`, `parent_pid`, `date_created`, `date_modified`) VALUES
(1, 'Kalimdor', 'continent', 3, NULL, '2019-02-08 19:34:26', '2019-02-08 19:34:26'),
(2, 'Eastern Kingdoms', 'continent', 3, NULL, '2019-02-08 19:34:56', '2019-02-08 19:34:56'),
(3, 'Feralas', 'zone', 3, 1, '2019-02-08 19:35:25', '2019-02-08 19:35:25'),
(4, 'Thalanaar', 'town', 3, 3, '2019-02-08 19:37:13', '2019-02-08 19:37:13');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
