<?php
if(!isset($_COOKIE['username'])) {
	header('Location: /login.php');
}
$from = $_POST['from'];
$to = $_POST['to'];
$who = $_POST['who'];
$border = $_POST['border'];

$a = (int)($from/8);
$b = (int)($from%8);
$c = (int)($to/8);
$d = (int)($to%8);

$host = "127.0.0.1";
$port = 1234;

$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Ошибка\n");
$result = socket_connect($socket, $host, $port) or die("Ошибка#2\n");

$message = $_COOKIE['username']."|".$who."|".$a.",".$b.",".$c.",".$d;

socket_write($socket, $message, strlen($message)) or die("Невозможно отправить сообщение\n");
$board = socket_read ($socket, 1024) or die("Невозможно получить ответ от сервера\n");

socket_close($socket);

echo $board;
?>