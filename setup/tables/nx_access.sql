-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 07, 2019 at 06:07 PM
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
-- Table structure for table `nx_access`
--

DROP TABLE IF EXISTS `nx_access`;
CREATE TABLE IF NOT EXISTS `nx_access` (
  `accessid` varchar(16) NOT NULL COMMENT 'item id hash',
  `name` varchar(64) DEFAULT NULL,
  `edit_accessid` varchar(16) DEFAULT NULL COMMENT 'optionally reference aditional access ids for eit (if null, then refers to self)',
  `utag` int(11) NOT NULL COMMENT 'user tag',
  `alid` int(11) NOT NULL COMMENT 'access level id',
  `whiteusers` varchar(512) DEFAULT NULL COMMENT 'whitelist for user tags',
  `blackusers` varchar(512) DEFAULT NULL COMMENT 'blacklist for user tags',
  `whitegroups` varchar(512) DEFAULT NULL COMMENT 'whitelist for group tags',
  `blackgroups` varchar(512) DEFAULT NULL COMMENT 'blacklist for group tags',
  `date_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`accessid`),
  KEY `utag` (`utag`,`alid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nx_access`
--

INSERT INTO `nx_access` (`accessid`, `name`, `edit_accessid`, `utag`, `alid`, `whiteusers`, `blackusers`, `whitegroups`, `blackgroups`, `date_modified`) VALUES
('private', 'Private', NULL, 0, 3, NULL, NULL, NULL, NULL, '2019-02-07 17:19:51'),
('public_editable', 'Open (public can edit)', NULL, 0, 0, NULL, NULL, NULL, NULL, '2019-02-07 17:19:03'),
('public_view', 'Public view', 'private', 0, 0, NULL, NULL, NULL, NULL, '2019-02-07 17:18:42');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
