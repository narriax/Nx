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
-- Table structure for table `nx_char_skills`
--

DROP TABLE IF EXISTS `nx_char_skills`;
CREATE TABLE IF NOT EXISTS `nx_char_skills` (
  `id` int(8) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL,
  `type` varchar(16) NOT NULL,
  `wid` int(4) NOT NULL COMMENT 'world index',
  `parent_sid` int(8) DEFAULT NULL COMMENT 'parent skill id',
  `description` varchar(256) DEFAULT NULL,
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `wid` (`wid`)
) ENGINE=MyISAM AUTO_INCREMENT=13 DEFAULT CHARSET=utf32;

--
-- Dumping data for table `nx_char_skills`
--

INSERT INTO `nx_char_skills` (`id`, `name`, `type`, `wid`, `parent_sid`, `description`, `date_created`, `date_modified`) VALUES
(1, 'Death Knight', 'class', 3, NULL, NULL, '2019-02-09 22:20:50', '2019-02-09 22:20:50'),
(2, 'Demon Hunter', 'class', 3, NULL, NULL, '2019-02-09 22:20:50', '2019-02-09 22:20:50'),
(3, 'Druid', 'class', 3, NULL, NULL, '2019-02-09 22:21:20', '2019-02-09 22:21:20'),
(4, 'Hunter', 'class', 3, NULL, NULL, '2019-02-09 22:21:20', '2019-02-09 22:21:20'),
(5, 'Mage', 'class', 3, NULL, NULL, '2019-02-09 22:21:44', '2019-02-09 22:21:44'),
(6, 'Monk', 'class', 3, NULL, NULL, '2019-02-09 22:21:44', '2019-02-09 22:21:44'),
(7, 'Paladin', 'class', 3, NULL, NULL, '2019-02-09 22:22:10', '2019-02-09 22:22:10'),
(8, 'Priest', 'class', 3, NULL, NULL, '2019-02-09 22:22:10', '2019-02-09 22:22:10'),
(9, 'Rogue', 'class', 3, NULL, NULL, '2019-02-09 22:22:37', '2019-02-09 22:22:37'),
(10, 'Shaman', 'class', 3, NULL, NULL, '2019-02-09 22:22:37', '2019-02-09 22:22:37'),
(11, 'Warllock', 'class', 3, NULL, NULL, '2019-02-09 22:22:55', '2019-02-09 22:22:55'),
(12, 'Warrior', 'class', 3, NULL, NULL, '2019-02-09 22:22:55', '2019-02-09 22:22:55');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
