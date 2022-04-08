<html>
	<h1>Registrazione</h1>
	<form action="/register.php" method="POST">
		<input type="text" name="username" placeholder="username"/>
		<input type="password" name="password" placeholder="password"/>
		<input type="submit" value="Submit" />
	</form>
	<a href="/index.php">Login</a>

	<?php
		if($_SERVER['REQUEST_METHOD'] == "POST"){
			if(isset($_POST['username']) && isset($_POST['password'])){
				$username = $_POST['username'];
				$password = $_POST['password'];
				$hpassword = password_hash($password, PASSWORD_DEFAULT);
				
				$users_file = file_get_contents("users.json");
				$users = json_decode($users_file, true);
				$users[$username] = $hpassword;

				$users_json = json_encode($users);
				file_put_contents("users.json", $users_json);
			}
		}

	?>
</html>