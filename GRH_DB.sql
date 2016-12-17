-- MySQL dump 10.15  Distrib 10.0.28-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: localhost
-- ------------------------------------------------------
-- Server version	10.0.28-MariaDB-1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Utilisateur`
--

DROP TABLE IF EXISTS `Utilisateur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Utilisateur` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `cin` varchar(10) NOT NULL,
  `username` varchar(30) DEFAULT NULL,
  `password` varchar(50) NOT NULL,
  `nom` varchar(30) NOT NULL,
  `prenom` varchar(30) NOT NULL,
  `dns` varchar(12) DEFAULT NULL,
  `cnss` varchar(10) DEFAULT NULL,
  `sexe` varchar(10) DEFAULT NULL,
  `email` varchar(30) NOT NULL,
  `num_tel` varchar(15) DEFAULT NULL,
  `ville` varchar(30) DEFAULT NULL,
  `adresse` varchar(100) DEFAULT NULL,
  `role` varchar(50) NOT NULL,
  `etat` varchar(30) DEFAULT 'Employé',
  `experience` varchar(200) DEFAULT NULL,
  `lang` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=74 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Utilisateur`
--

LOCK TABLES `Utilisateur` WRITE;
/*!40000 ALTER TABLE `Utilisateur` DISABLE KEYS */;
INSERT INTO `Utilisateur` VALUES (1,'12345678','admin','admin','admin','admin','01/01/1990','123123','Homme','admin@mail.com','12345678','Tunis','Tunis','role_admin','Employe','test','test'),(60,'09312343','user1','user1','Mohamed','Ali','01/06/1990','2456','Homme','med.ali@gmail.com','20123456','Tunis','Manouba','Employe','Employe','Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has','Arabe Englais'),(61,'01423574','user2','user2','Samia','Gharbi','02/12/1987','87547','Femme','samia.gharbi@gmail.com','50326857','Sousse','Msaken','Employe','Employe','Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has','Arabe'),(63,'87696542','user4','user4','Mohamed','Amine','02/1998','1234','Homme','med.amine@gmail.com','98568745','Tunis','Tunis','Employe','Employe','Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has','FR'),(64,'08452414','user5','user5','Foued','Bangagi','22/03/1993','584785','Homme','Foued@hotmail.com','32568112','Beja','Tunis 4000','Employe','Employe','Experience 100ans devlopment Info.','Tous'),(65,'07854524','user6','user6','Abdlhak','Rihab','14/01/1995','0012541','Femme','Rihab@yahoo.fr','24587524','Manoub','Tunis','Employe','Employe','Experience 99ans Multimedia','FR,Eng,Ar'),(66,'09337773','res1','res1','Mansour','Hosni',NULL,NULL,NULL,'mail@hosni.me',NULL,NULL,NULL,'Responsable','Employe',NULL,NULL),(67,'02145241','res2','res2','Mbarki','Chadi',NULL,NULL,NULL,'mbarki.chadi@live.fr',NULL,NULL,NULL,'Responsable','Employe',NULL,NULL),(68,'45214452','res3','res3','Rami','Ben Amor',NULL,NULL,NULL,'rami.ben.amor@outlook.fr',NULL,NULL,NULL,'Responsable','Employe',NULL,NULL),(70,'02154224','user3','user3','Meselmani','Nidhal','20/11/1995','1234','Homme','nidhal@outlook.com','40256821','Tunis','Tunis','Employe','Employe','Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has','Arabe'),(71,'01230112','user','user','user','user','01/01/1990','12345','Homme','user@user.com','78544122','Tunis','Tunis','Employe','Employe congedie',NULL,NULL),(72,'123456','testdel','testdel','testdel','testdel','01/02/1995','123456','Homme','testdel@testdel.com','87542145','testdel','testdel','Employe','Employe',NULL,NULL);
/*!40000 ALTER TABLE `Utilisateur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `competence`
--

DROP TABLE IF EXISTS `competence`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `competence` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nomc` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=43 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `competence`
--

LOCK TABLES `competence` WRITE;
/*!40000 ALTER TABLE `competence` DISABLE KEYS */;
INSERT INTO `competence` VALUES (1,'JEE'),(2,'Android'),(3,'Conception graphique'),(4,'(null)'),(5,'(null)'),(6,'(null)'),(7,'test'),(8,'test2'),(9,'tes3'),(10,'test4'),(11,'test 5'),(12,'zaeaze'),(13,'sd'),(14,'qsd'),(15,'sd'),(16,'888'),(17,'999'),(18,'000'),(19,'J2EE'),(20,'Java'),(21,'C++'),(22,'UML'),(23,'Java'),(24,'.net'),(25,'PHP'),(26,'Android'),(27,'J2EE'),(28,'JAVA'),(29,'C'),(30,'AngulairJs'),(31,'NodeJs'),(32,'Android'),(33,'Iphone'),(34,'PHP'),(35,'Objective C'),(36,'c ++'),(37,'J2ee'),(38,'C'),(39,'Unity'),(40,'3D'),(41,'Maya'),(42,'Javascript');
/*!40000 ALTER TABLE `competence` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `condidat`
--

DROP TABLE IF EXISTS `condidat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `condidat` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `cin` varchar(10) NOT NULL,
  `nom` varchar(30) DEFAULT NULL,
  `prenom` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `condidat`
--

LOCK TABLES `condidat` WRITE;
/*!40000 ALTER TABLE `condidat` DISABLE KEYS */;
/*!40000 ALTER TABLE `condidat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `conge`
--

DROP TABLE IF EXISTS `conge`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `conge` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `id_emp` int(5) NOT NULL,
  `date_deb` varchar(30) DEFAULT NULL,
  `date_fin` varchar(50) DEFAULT NULL,
  `etat` varchar(20) DEFAULT 'en cour',
  `raison` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `cle_prim` (`id_emp`),
  CONSTRAINT `cle_prim` FOREIGN KEY (`id_emp`) REFERENCES `Utilisateur` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `conge`
--

LOCK TABLES `conge` WRITE;
/*!40000 ALTER TABLE `conge` DISABLE KEYS */;
INSERT INTO `conge` VALUES (11,60,'26/12/2016','9/1/2017','en cour','Voyage'),(12,60,'8/1/2017','14/2/2017','en cour','Voyage 2'),(13,61,'2/2/2017','4/2/2017','en cour','Maladie'),(14,63,'2/2/2017','3/2/2018','en cour','Voyage1'),(15,63,'2/2/2017','3/2/2017','en cour','Voyage2'),(16,63,'5/2/2017','8/2/2017','en cour','Voyage3'),(17,64,'2/2/2017','4/3/2017','en cour','CongÃ© Annuelle'),(18,65,'2/2/2017','3/3/2018','en cour','raison personelle');
/*!40000 ALTER TABLE `conge` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `diplome`
--

DROP TABLE IF EXISTS `diplome`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `diplome` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `NomD` varchar(50) DEFAULT NULL,
  `anne` varchar(5) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `diplome`
--

LOCK TABLES `diplome` WRITE;
/*!40000 ALTER TABLE `diplome` DISABLE KEYS */;
INSERT INTO `diplome` VALUES (1,'Licence Info',NULL),(2,'Bac','2013'),(3,'master','2016'),(4,'phd','2016'),(5,'phd','2019'),(6,'aze','aze'),(7,'Bac','2013'),(8,'Licence Info','2016'),(9,'Bac','2012'),(10,'Licence Info','2014'),(11,'Master','2017'),(12,'Bac','2012'),(13,'Ing','2019'),(14,'Bac','2010'),(15,'Licence CM','2016'),(16,'Bac','2013'),(17,'Licence','2016');
/*!40000 ALTER TABLE `diplome` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `offre_emploi`
--

DROP TABLE IF EXISTS `offre_emploi`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `offre_emploi` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(50) NOT NULL,
  `desc` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `offre_emploi`
--

LOCK TABLES `offre_emploi` WRITE;
/*!40000 ALTER TABLE `offre_emploi` DISABLE KEYS */;
/*!40000 ALTER TABLE `offre_emploi` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `salaire`
--

DROP TABLE IF EXISTS `salaire`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `salaire` (
  `id_sal` int(5) NOT NULL AUTO_INCREMENT,
  `id_emp` int(5) NOT NULL,
  `montant` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`id_sal`),
  KEY `cle_prim_sal` (`id_emp`),
  CONSTRAINT `cle_prim_sal` FOREIGN KEY (`id_emp`) REFERENCES `Utilisateur` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `salaire`
--

LOCK TABLES `salaire` WRITE;
/*!40000 ALTER TABLE `salaire` DISABLE KEYS */;
INSERT INTO `salaire` VALUES (14,60,'200dt'),(15,61,'-'),(16,63,'3000dt'),(17,64,'-');
/*!40000 ALTER TABLE `salaire` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `utilisateur_competence`
--

DROP TABLE IF EXISTS `utilisateur_competence`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `utilisateur_competence` (
  `id_u` int(5) NOT NULL,
  `id_c` int(11) NOT NULL,
  `etat` int(1) NOT NULL,
  PRIMARY KEY (`id_u`,`id_c`),
  KEY `fgk_comp` (`id_c`),
  CONSTRAINT `fgk_comp` FOREIGN KEY (`id_c`) REFERENCES `competence` (`id`) ON DELETE CASCADE,
  CONSTRAINT `fgk_user` FOREIGN KEY (`id_u`) REFERENCES `Utilisateur` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `utilisateur_competence`
--

LOCK TABLES `utilisateur_competence` WRITE;
/*!40000 ALTER TABLE `utilisateur_competence` DISABLE KEYS */;
INSERT INTO `utilisateur_competence` VALUES (60,19,1),(60,20,1),(60,21,1),(60,22,1),(61,23,1),(61,24,0),(61,25,1),(61,26,0),(63,32,1),(63,33,0),(63,34,1),(63,35,1),(63,36,1),(64,37,1),(64,38,1),(65,39,1),(65,40,1),(65,41,1),(65,42,0),(70,27,1),(70,28,0),(70,29,1),(70,30,0),(70,31,1);
/*!40000 ALTER TABLE `utilisateur_competence` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `utilisateur_diplome`
--

DROP TABLE IF EXISTS `utilisateur_diplome`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `utilisateur_diplome` (
  `id_u` int(5) NOT NULL,
  `id_d` int(11) NOT NULL,
  `etat` int(1) NOT NULL,
  KEY `fgk_dip` (`id_d`),
  KEY `fgk_dim_user` (`id_u`),
  CONSTRAINT `fgk_dim_user` FOREIGN KEY (`id_u`) REFERENCES `Utilisateur` (`id`) ON DELETE CASCADE,
  CONSTRAINT `fgk_dip` FOREIGN KEY (`id_d`) REFERENCES `diplome` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `utilisateur_diplome`
--

LOCK TABLES `utilisateur_diplome` WRITE;
/*!40000 ALTER TABLE `utilisateur_diplome` DISABLE KEYS */;
INSERT INTO `utilisateur_diplome` VALUES (60,7,1),(60,8,1),(61,9,1),(61,10,0),(61,11,1),(70,12,0),(70,13,1),(63,14,0),(64,15,0),(65,16,1),(65,17,1);
/*!40000 ALTER TABLE `utilisateur_diplome` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-12-16  1:17:06
