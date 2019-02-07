-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 07, 2019 at 06:08 PM
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
-- Table structure for table `nx_worlds`
--

DROP TABLE IF EXISTS `nx_worlds`;
CREATE TABLE IF NOT EXISTS `nx_worlds` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL,
  `universe_id` int(4) NOT NULL,
  `owner_tag` varchar(16) DEFAULT NULL,
  `accessid` varchar(16) DEFAULT NULL COMMENT 'access id hash',
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `desc` text NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  KEY `universe_id` (`universe_id`,`owner_tag`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nx_worlds`
--

INSERT INTO `nx_worlds` (`id`, `name`, `universe_id`, `owner_tag`, `accessid`, `date_created`, `date_modified`, `desc`) VALUES
(1, 'Earth', 1, NULL, NULL, '2017-06-30 23:50:24', '2017-06-30 23:50:24', ''),
(2, 'DnD', 2, NULL, NULL, '2017-06-30 23:52:02', '2017-06-30 23:52:02', ''),
(3, 'Warcraft', 2, NULL, NULL, '2017-06-30 23:52:48', '2017-06-30 23:52:48', ''),
(4, 'Lorein', 3, 'kirenno', 'private', '2019-02-07 00:18:23', '2019-02-07 00:18:23', '');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
