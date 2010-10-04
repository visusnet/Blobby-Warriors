<?php
	require("mysql.php");

	$user = $_GET['user'];

	$time = time();

	mysql_query("UPDATE tab_user SET lastSeen = '$time' WHERE username = '$user';")
		or die("lol". mysql_error());
?>
