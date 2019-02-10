-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 10, 2019 at 01:22 AM
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
-- Table structure for table `nx_char_properties`
--

DROP TABLE IF EXISTS `nx_char_properties`;
CREATE TABLE IF NOT EXISTS `nx_char_properties` (
  `id` int(8) NOT NULL AUTO_INCREMENT,
  `property_group` varchar(16) NOT NULL,
  `name` varchar(32) NOT NULL,
  `datatype` varchar(8) NOT NULL,
  `possible_values` text NOT NULL,
  `count_limit` int(2) NOT NULL DEFAULT '-1',
  `wid` int(4) DEFAULT NULL COMMENT 'world id where this is applicable',
  `description` varchar(64) DEFAULT NULL,
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=28 DEFAULT CHARSET=utf32;

--
-- Dumping data for table `nx_char_properties`
--

INSERT INTO `nx_char_properties` (`id`, `property_group`, `name`, `datatype`, `possible_values`, `count_limit`, `wid`, `description`, `date_created`, `date_modified`) VALUES
(1, 'name', 'name-first', 'string', '', -1, NULL, 'first / given name', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(2, 'name', 'name-nick', 'string', '', -1, NULL, 'nick name or personal title', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(3, 'name', 'name-last', 'string', '', -1, NULL, 'last / family name', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(4, 'name', 'name-middle', 'string', '', -1, NULL, 'additional given name', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(5, 'name', 'name-patronymic', 'string', '', 1, NULL, 'patronymic name (middle name alternative in some cultures)', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(10, 'name', 'title', 'string', '', -1, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(6, 'name', 'name-matronymic', 'string', '', 1, NULL, 'matronymic name (middle name alternative in some cultures)', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(9, 'name', 'clan name', 'string', '', -1, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(7, 'name', 'prefix', 'string', '', -1, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(8, 'name', 'suffix', 'string', '', -1, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(12, 'demographics', 'race', 'string', '@nx_char_races.id', -1, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(13, 'demographics', 'dob', 'string', '#YEAR', 1, NULL, 'date of birth', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(14, 'demographics', 'dod', 'string', '#YEAR', 1, NULL, 'date of death', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(15, 'demographics', 'gender', 'string', 'male,female', 1, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(16, 'demographics', 'ethnicity', 'string', '#ETHNICITY', -1, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(17, 'demographics', 'pob', 'string', '@nx_maps_places.id', 1, NULL, 'place of birth', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(18, 'demographics', 'pod', 'string', '@nx_maps_places.id', 1, NULL, 'place of death', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(19, 'demographics', 'parent_charid', 'int', '@nx_chars.id', 2, NULL, 'biological parent (character id)', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(20, 'demographics', 'guardian_charid', 'int', '@nx_chars.id', -1, NULL, 'adopted parent or guardian (character id)', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(21, 'description', 'color', 'hex', '#COLOR', 2, NULL, 'arbitrary', '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(22, 'description', 'icon', 'string', '#ICON', 1, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(23, 'description', 'eye_color', 'hex', '#COLOR', 2, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(24, 'description', 'hair_color', 'hex', '#COLOR', 2, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37'),
(27, '', 'skill', 'string', '@nx_char_skills.id', -1, NULL, NULL, '2019-02-09 00:21:37', '2019-02-09 00:21:37');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
