-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Jun 30, 2017 at 10:01 PM
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
-- Table structure for table `nx_chars`
--

CREATE TABLE IF NOT EXISTS `nx_chars` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `alias` varchar(16) NOT NULL,
  `world_id` int(4) NOT NULL,
  `owner_tag` varchar(16) DEFAULT NULL,
  `access_level` int(1) NOT NULL DEFAULT '0',
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `alias` (`alias`),
  KEY `owner_uid` (`owner_tag`),
  KEY `world_id` (`world_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `nx_chars`
--

INSERT INTO `nx_chars` (`id`, `alias`, `world_id`, `owner_tag`, `access_level`, `date_created`, `date_modified`) VALUES
(1, 'Arderian', 3, 'narriax', 4, '2017-06-30 20:01:44', '2017-06-30 20:01:44');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
