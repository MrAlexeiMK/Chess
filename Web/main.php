<?php
if(!isset($_COOKIE['username'])) {
    header('Location: /login.php');
}
if(isset($_POST['exit'])) {
    unset($_COOKIE['username']);
    setcookie('username', null, -1, '/');
    header('Location: /login.php');
}
$you_white = true;
if(isset($_POST['choose'])) {
	if($_POST['type'] == "white") $you_white = true;
	else if($_POST['type'] == "black") $you_white = false;
}
else $_POST['type'] = "white";

$who = "me";
$username = $_COOKIE['username'];
$con = new mysqli("127.0.0.1", "root", "", "chess");
$stmt = $con->prepare("SELECT rating FROM users WHERE user = ?");
$stmt->bind_param('s', $username);
$stmt->execute();
$result = $stmt->get_result();
$user = $result->fetch_object();
$rating = $user->rating;

$host = "127.0.0.1";
$port = 1234;

?>
<script>
var interval = 600;
pred = -1

function step(index, isEmpty, who, border) {
	if($('#result_image').attr("src") == undefined) {
		if(pred == -1) {
			if(!isEmpty) {
				pred = index;
				$("#hidden").css("background-color", $("#"+pred).css("background-color"));
				$("#"+pred).css("background", "#d5bdbd");
			}
		}
		else {
			$("#"+pred).css("background-color", $("#hidden").css("background-color"));
			$.ajax({
			   type: "POST",
			   url: 'doStep.php',
			   data:{from: pred, to: index, who: who, border: border},
			   success:function(res) {
				   if(res != "impossible") {
						window.location.reload(false);
				   }
				   else {
						if(!isEmpty) {
						pred = index;
						$("#hidden").css("background-color", $("#"+pred).css("background-color"));
						$("#"+pred).css("background", "#d5bdbd");
			}
				   }
			   }

			});
			pred = -1;
		}
	}
}

function update() {
    $.ajax({
            type: 'POST',
            url: 'ai.php',
            success: function (data) {
                if(data != "No change") $('#board').html(data); 
            },
            complete: function (data) {
                setTimeout(update, interval);
            }
    });
}
setTimeout(update, interval);

</script>
<html>
<head>
<script src="scripts/jquery.js"></script>
<link rel="stylesheet" href="styles/styles.css">
</head>
<body>

<div id="menu">
<h3 id="nickname"><?=$username?> (рейтинг: <?=$rating?>)</h3>
    <form action="main.php" method="POST">
        <input type="submit" value="Главная" name="main"> <br />
        <input type="submit" value="Игроки" name="players"> <br />
        <input type="submit" value="Против ИИ" name="ai"> <br />
        <input type="submit" value="Выйти" name="exit"> <br />
		
		<div id="type">
			<?
			if(!isset($_POST['choose']) and !isset($_POST['players']) and !isset($_POST['ai'])) {
				if($you_white) {
					echo "<input type='radio' id='white' name='type' value='white' checked>";
				}
				else echo "<input type='radio' id='white' name='type' value='white'>";
				echo "<label for='white'>За белых</label><br>";
				if(!$you_white) {
					echo "<input type='radio' id='black' name='type' value='black' checked>";
				}
				else echo "<input type='radio' id='black' name='type' value='black'>";
				echo "<label for='black'>За чёрных</label><br>";
				echo "<input type='submit' value='Выбор' name='choose'> <br />";
			}
			?>
		</div>
    </form>
</div>
<div id="menu2">
<?
if(isset($_POST['players'])) {
	$who = "player";
	$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Ошибка\n");
	$result = socket_connect($socket, $host, $port) or die("Ошибка#2\n");
	$message = $username."|".$who."|players";
	socket_write($socket, $message, strlen($message)) or die("Невозможно тправить сообщение\n");
	socket_close($socket);
}
else if(isset($_POST['ai'])) {
	$who = "ai";
	echo "<p>Попробуйте одолеть искуственный интеллект, который обучается даже во время игры!</p>";
}
else {
	$who = "me";
	echo "<p>Добро пожаловать в Шахматы</p>";
	echo "<p>Используйте доску справа для игры с самим собой</p>";
	echo "<p>Нажмите кнопку 'Игроки' для выбора реального соперника онлайн</p>";
	echo "<p>Нажмите кнопку 'Против ИИ' для игры против искуственного интеллекта</p>";
	echo "<p>Искуственный интеллект обучается даже во время игры</p>";
	echo "<p>Удачи!</p>";
}
?>
</div>

<div id="board">
<?
if (!isset($_POST['exit'])) {
	if(isset($_POST['main'])) {
		$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Ошибка\n");
		$result = socket_connect($socket, $host, $port) or die("Ошибка#2\n");
		$message = $username."|".$who."|".$_POST['type']."|remove";
		socket_write($socket, $message, strlen($message)) or die("Невозможно тправить сообщение\n");
		socket_close($socket);
	}
	else if ($who == "me" and isset($_POST['choose'])) {
		$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Ошибка\n");
		$result = socket_connect($socket, $host, $port) or die("Ошибка#2\n");
		$message = $username."|".$who."|".$_POST['type'];
		socket_write($socket, $message, strlen($message)) or die("Невозможно тправить сообщение\n");
		$read = socket_read ($socket, 1024) or die("Невозможно получить ответ от сервера\n");
		$arr = explode('|', $read);
		$board = $arr[0];
		$status = $arr[1];
		socket_close($socket);
		if(!isset($_POST['main'])) {
			echo "<table border='1' id='table'>";
			$ch = $you_white;
			$index = 0;
			for($i = 0; $i < 8; $i++) {
				echo "<tr>";
				for($j = 0; $j < 4; $j++) {
					$ind = $index;
					$a = $ind;
					$b = $ind+1;
					if($_POST['type'] == "black") {
						$ind = 63-$ind;
						$a = $ind;
						$b = $ind-1;
					}
					$s1 = mb_substr($board, $index, 1);
					$s2 = mb_substr($board, $index+1, 1);
					if($ch) {
						if($s1 != ' ') echo "<td id='".$a."' onClick='step(".$a.", false, \"".$who."\", \"".$board."\")' style='background-color: #eeeed2'><img draggable ='false' src='icons/".$s1.".png'></img></td>";
						else echo "<td id='".$a."' onClick='step(".$a.", true, \"".$who."\", \"".$board."\")'    style='background-color: #eeeed2'><img draggable ='false'  srrc='icons/".$s1.".png'></img></td>";
						if($s2 != ' ') echo "<td id='".$b."' onClick='step(".$b.", false, \"".$who."\", \"".$board."\")' style='background-color: #769656'><img draggable ='false' src='icons/".$s2.".png'></img></td>";
						else echo "<td id='".$b."' onClick='step(".$b.", true, \"".$who."\", \"".$board."\")'  style='background-color: #769656'><img draggable ='false' srrc='icons/".$s2.".png'></img></td>";
					}
					else {
						if($s1 != ' ') echo "<td id='".$a."' onClick='step(".$a.", false, \"".$who."\", \"".$board."\")' style='background-color: #769656'><img draggable ='false' src='icons/".$s1.".png'></img></td>";
						else echo "<td id='".$a."' onClick='step(".$a.", true, \"".$who."\", \"".$board."\")' style='background-color: #769656'><img draggable ='false' srrc='icons/".$s1.".png'></img></td>";
						if($s2 != ' ') echo "<td id='".$b."' onClick='step(".$b.", false, \"".$who."\", \"".$board."\")' style='background-color: #eeeed2'><img draggable ='false' src='icons/".$s2.".png'></img></td>";
						else echo "<td id='".$b."' onClick='step(".$b.", true, \"".$who."\", \"".$board."\")' style='background-color: #eeeed2'><img draggable ='false' srrc='icons/".$s2.".png'></img></td>";
					}
					$index+=2;
				}
				$ch = !$ch;
				echo "</tr>";
			}
			echo "</table>";
		}
		if($status != "ingame") {
			echo "<div id = 'result'>";
			echo "<img id='result_image' class = 'res' src = 'icons/".$status.".png'></img>";
			echo "</div>";
		}
	}
	else if($who == "ai") {
		$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Ошибка\n");
		$result = socket_connect($socket, $host, $port) or die("Ошибка#2\n");
		$message = $username."|".$who."|"."load";
		socket_write($socket, $message, strlen($message)) or die("Невозможно тправить сообщение\n");
		$read = socket_read ($socket, 1024) or die("Невозможно получить ответ от сервера\n");
		if($read != "No change") {
			$arr = explode('|', $read);
			$board = $arr[0];
			$status = $arr[1];
			$type = $arr[2];
			if($type == "black") $you_white = false;
			
			socket_close($socket);
			if(!isset($_POST['main'])) {
				echo "<table border='1' id='table'>";
				$ch = $you_white;
				$index = 0;
				for($i = 0; $i < 8; $i++) {
					echo "<tr>";
					for($j = 0; $j < 4; $j++) {
						$ind = $index;
						$a = $ind;
						$b = $ind+1;
						if($type == "black") {
							$ind = 63-$ind;
							$a = $ind;
							$b = $ind-1;
						}
						$s1 = mb_substr($board, $index, 1);
						$s2 = mb_substr($board, $index+1, 1);
						if($ch) {
							if($s1 != ' ') echo "<td id='".$a."' onClick='step(".$a.", false, \"".$who."\", \"".$board."\")' style='background-color: #eeeed2'><img draggable ='false' src='icons/".$s1.".png'></img></td>";
							else echo "<td id='".$a."' onClick='step(".$a.", true, \"".$who."\", \"".$board."\")'    style='background-color: #eeeed2'><img draggable ='false'  srrc='icons/".$s1.".png'></img></td>";
							if($s2 != ' ') echo "<td id='".$b."' onClick='step(".$b.", false, \"".$who."\", \"".$board."\")' style='background-color: #769656'><img draggable ='false' src='icons/".$s2.".png'></img></td>";
							else echo "<td id='".$b."' onClick='step(".$b.", true, \"".$who."\", \"".$board."\")'  style='background-color: #769656'><img draggable ='false' srrc='icons/".$s2.".png'></img></td>";
						}
						else {
							if($s1 != ' ') echo "<td id='".$a."' onClick='step(".$a.", false, \"".$who."\", \"".$board."\")' style='background-color: #769656'><img draggable ='false' src='icons/".$s1.".png'></img></td>";
							else echo "<td id='".$a."' onClick='step(".$a.", true, \"".$who."\", \"".$board."\")' style='background-color: #769656'><img draggable ='false' srrc='icons/".$s1.".png'></img></td>";
							if($s2 != ' ') echo "<td id='".$b."' onClick='step(".$b.", false, \"".$who."\", \"".$board."\")' style='background-color: #eeeed2'><img draggable ='false' src='icons/".$s2.".png'></img></td>";
							else echo "<td id='".$b."' onClick='step(".$b.", true, \"".$who."\", \"".$board."\")' style='background-color: #eeeed2'><img draggable ='false' srrc='icons/".$s2.".png'></img></td>";
						}
						$index+=2;
					}
					$ch = !$ch;
					echo "</tr>";
				}
				echo "</table>";
			}
			if($status != "ingame") {
				echo "<div id = 'result'>";
				echo "<img id='result_image' class = 'res' src = 'icons/".$status.".png'></img>";
				echo "</div>";
			}
		}
		else {
			echo "No change";
		}
	}
}
?>

</div>
<p id="hidden" hidden></p>

</body>
</html>