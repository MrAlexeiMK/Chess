<?php
    if(!isset($_COOKIE['username'])) {
        header('Location: /login.php');
    }
    else {
        header('Location: /main.php');
    }
?>