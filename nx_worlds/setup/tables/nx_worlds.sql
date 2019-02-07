-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Aug 12, 2017 at 12:35 AM
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
-- Table structure for table `nx_worlds`
--

CREATE TABLE IF NOT EXISTS `nx_worlds` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL,
  `universe_id` int(4) NOT NULL,
  `owner_tag` varchar(16) DEFAULT NULL,
  `accessid` varchar(16) NOT NULL DEFAULT '',
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `desc` text NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  KEY `universe_id` (`universe_id`,`owner_tag`,`accessid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `nx_worlds`
--

INSERT INTO `nx_worlds` (`id`, `name`, `universe_id`, `owner_tag`, `accessid`, `date_created`, `date_modified`, `desc`) VALUES
(1, 'Earth', 1, NULL, '', '2017-06-30 19:50:24', '2017-06-30 19:50:24', ''),
(2, 'DnD', 2, NULL, '', '2017-06-30 19:52:02', '2017-06-30 19:52:02', ''),
(3, 'Warcraft', 2, NULL, '', '2017-06-30 19:52:48', '2017-06-30 19:52:48', ''),
(4, 'Lorein', 3, NULL, '', '2017-06-30 19:52:48', '2017-06-30 19:52:48', '');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
