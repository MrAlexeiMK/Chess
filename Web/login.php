<?php
if (!empty($_POST)) {
    if(isset($_POST['register'])) {
        header('Location: reg.php');
    }
    if(isset($_POST['username']) && isset($_POST['password']) && $_POST['username'] != "" && $_POST['password'] != "") {
        $con = new mysqli("127.0.0.1", "root", "", "chess");
        $stmt = $con->prepare("SELECT password FROM users WHERE user = ?");
        $stmt->bind_param('s', $_POST['username']);
        $stmt->execute();
        $result = $stmt->get_result();
        $user = $result->fetch_object();
        if(is_null($user)) {
            echo "Пользователь не найден";
        }
        else {
            if($_POST['password'] == $user->password) {
                setcookie('username', $_POST['username']);
                header('Location: /main.php');
            }
            else {
                echo "Неверный пароль";
            }
        }
    }
    else {
        echo "Заполните все поля!";
    }
}
?>
<div id="login">
<h3>Авторизация</h3>
<form action="login.php" method="POST" id="enter">
    <input type="text" name="username" id="username" placeholder="Никнейм" /> <br />
    <input type="password" name="password" id="password" placeholder="Пароль" /> <br />
    <input type="submit" name="enter" value="Войти" />
    <input type="submit" name="register" value="Зарегистрироваться"/> <br />
</form>
</div>