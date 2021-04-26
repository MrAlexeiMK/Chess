<?php
		$host = "127.0.0.1";
		$port = 1234;
		$username = $_COOKIE['username'];
		$who = "ai";
		$you_white = true;
		
		$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Ошибка\n");
		$result = socket_connect($socket, $host, $port) or die("Ошибка#2\n");
		$message = $username."|".$who."|"."update";
		socket_write($socket, $message, strlen($message)) or die("Невозможно тправить сообщение\n");
		$read = socket_read ($socket, 1024) or die("Невозможно получить ответ от сервера\n");
		if($read != "No change") {
			$arr = explode('|', $read);
			$board = $arr[0];
			$status = $arr[1];
			if($status == "ingame") {
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
		else {
			echo "No change";
		}
?>