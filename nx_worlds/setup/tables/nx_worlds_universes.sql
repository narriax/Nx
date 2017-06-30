-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Jun 30, 2017 at 09:57 PM
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
  `access_level` int(2) NOT NULL DEFAULT '0',
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `desc` text NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  KEY `owner_uid` (`owner_tag`,`access_level`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `nx_worlds_universes`
--

INSERT INTO `nx_worlds_universes` (`id`, `name`, `owner_tag`, `access_level`, `date_created`, `date_modified`, `desc`) VALUES
(0, 'reality', NULL, 5, '2017-06-30 19:47:13', '2017-06-30 19:47:13', ''),
(1, 'DnD', NULL, 5, '2017-06-30 19:48:53', '2017-06-30 19:48:53', 'Dungeons and Dragons'),
(2, 'Warcraft', NULL, 4, '2017-06-30 19:49:18', '2017-06-30 19:49:18', '');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
