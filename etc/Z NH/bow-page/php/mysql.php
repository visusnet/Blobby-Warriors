<?php
	$db = mysql_connect("localhost", "web12", "jWTQWkY9")
		or die("Fehler beim Verbinden mit dem DB-Server: " . mysql_error());
		
	mysql_select_db("usr_web12_1", $db)
		or die("Fehler beim Verbinden mit der DB: " . mysql_error());
?>