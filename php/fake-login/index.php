<html>
	<h1>Login</h1>
	<form action="/index.php" method="POST">
		<input type="text" name="username" placeholder="username"/>
		<input type="password" name="password" placeholder="password"/>
		<input type="submit" value="Submit" />
	</form>
	<a href="/register.php">Registrati</a>

	<?php
		if($_SERVER['REQUEST_METHOD'] == 'POST') {
			$username = $_POST['username'];
			$password = $_POST['password'];

			$users_file = file_get_contents("users.json");
			$users = json_decode($users_file, true);

			if(isset($users[$username]) && password_verify($password, $users[$username])) {
				echo "Login effettuato con successo";
			} else {
				echo "Login fallito";
			}
		}
	?>


</html>