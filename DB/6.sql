-- MySQL dump 10.13  Distrib 8.0.11, for Win64 (x86_64)
--
-- Host: localhost    Database: bcp
-- ------------------------------------------------------
-- Server version	8.0.11

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
 SET NAMES utf8mb4 ;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `consume`
--

DROP TABLE IF EXISTS `consume`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `consume` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `id` int(11) NOT NULL,
  `name` char(40) NOT NULL,
  `dotdamage` float DEFAULT NULL,
  `healamount` float DEFAULT NULL,
  `speed` float DEFAULT NULL,
  `deffend` float DEFAULT NULL,
  `eattime` float DEFAULT NULL,
  `dottime` float DEFAULT NULL,
  `mesh` text,
  `thume` text,
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `consume`
--

LOCK TABLES `consume` WRITE;
/*!40000 ALTER TABLE `consume` DISABLE KEYS */;
INSERT INTO `consume` VALUES (1,1,'풀반창고',NULL,15,NULL,NULL,2,NULL,NULL,NULL),(2,2,'인내약',NULL,NULL,NULL,5,2,60,NULL,NULL),(3,3,'신속약',NULL,NULL,1.5,NULL,2,60,NULL,NULL),(4,4,'회복약',NULL,60,NULL,NULL,3,NULL,NULL,NULL),(5,5,'화살',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),(6,6,'불화살',5,NULL,NULL,NULL,NULL,3,NULL,NULL),(7,7,'독화살',3,NULL,NULL,NULL,NULL,5,NULL,NULL);
/*!40000 ALTER TABLE `consume` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `craft1`
--

DROP TABLE IF EXISTS `craft1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `craft1` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `id` int(11) NOT NULL,
  `name` char(40) NOT NULL,
  `creattime` float NOT NULL,
  `wood` int(11) DEFAULT NULL,
  `rock` int(11) DEFAULT NULL,
  `leaf` int(11) DEFAULT NULL,
  `leather` int(11) DEFAULT NULL,
  `bug` int(11) DEFAULT NULL,
  `mushroom` int(11) DEFAULT NULL,
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `craft1`
--

LOCK TABLES `craft1` WRITE;
/*!40000 ALTER TABLE `craft1` DISABLE KEYS */;
INSERT INTO `craft1` VALUES (1,1,'풀반창고',0.4,1,NULL,2,NULL,NULL,NULL),(2,2,'인내약',0.4,NULL,NULL,NULL,1,1,NULL),(3,3,'신속약',0.4,NULL,NULL,1,NULL,NULL,1),(4,4,'회복약',0.4,1,1,1,NULL,2,2),(5,5,'화살',0.4,1,1,NULL,NULL,NULL,NULL),(6,6,'불화살',0.4,1,1,1,NULL,NULL,NULL),(7,7,'독화살',0.4,1,1,NULL,NULL,NULL,1);
/*!40000 ALTER TABLE `craft1` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `equipment`
--

DROP TABLE IF EXISTS `equipment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `equipment` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `id` int(11) NOT NULL,
  `type` char(40) NOT NULL,
  `tear` int(11) NOT NULL DEFAULT '1',
  `name` char(40) NOT NULL,
  `damage` float NOT NULL,
  `stamcost` float NOT NULL,
  `delay` float NOT NULL,
  `range1` float DEFAULT NULL,
  `mesh` char(255) DEFAULT NULL,
  `thumb` char(255) DEFAULT NULL,
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `equipment`
--

LOCK TABLES `equipment` WRITE;
/*!40000 ALTER TABLE `equipment` DISABLE KEYS */;
INSERT INTO `equipment` VALUES (1,1,'한손도끼',1,'쇠도끼',10,20,1,50,NULL,NULL),(2,2,'활',1,'나무활',50,10,1,NULL,NULL,NULL),(3,3,'한손칼',2,'쇠칼',20,15,0.8,50,NULL,NULL),(4,4,'양손칼',2,'쇠대검',40,30,1.5,80,NULL,NULL),(5,5,'한손칼방패',2,'쇠칼방',15,20,1,50,NULL,NULL);
/*!40000 ALTER TABLE `equipment` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-06-18 15:20:40
