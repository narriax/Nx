-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Apr 29, 2017 at 01:53 AM
-- Server version: 5.6.17
-- PHP Version: 5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `bigbrother`
--

-- --------------------------------------------------------

--
-- Table structure for table `nx_user_setting_values`
--

CREATE TABLE IF NOT EXISTS `nx_user_setting_values` (
  `uid` int(10) unsigned NOT NULL,
  `sid` int(10) NOT NULL,
  `value` varchar(255) CHARACTER SET latin1 NOT NULL,
  PRIMARY KEY (`uid`,`sid`),
  KEY `sid_cascade` (`sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `nx_user_setting_values`
--
ALTER TABLE `nx_user_setting_values`
  ADD CONSTRAINT `uid_cascade` FOREIGN KEY (`uid`) REFERENCES `users` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `sid_cascade` FOREIGN KEY (`sid`) REFERENCES `nx_user_settings` (`sid`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
