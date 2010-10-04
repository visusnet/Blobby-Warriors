<?php
	require("mysql.php");


	$user=$_GET['user'];
	$pass=$_GET['pass'];
	$email=$_GET['email'];
	$date = date("Y-m-j H:i:s");


	$query = "SELECT * FROM tab_user WHERE username='$user';";

	$result = mysql_query($query)
		or die("1"); // serverfehler

	if(mysql_num_rows($result) != 0)
	{
		// user existiert bereits
		print("2");
		return;
	}

	mysql_query("INSERT INTO tab_user (username, password, lastSeen) VALUES ('$user', '$pass', '0')")
		or die("1");

	print("0");
?>
