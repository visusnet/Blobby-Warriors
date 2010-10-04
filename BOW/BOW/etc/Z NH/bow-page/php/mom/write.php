<?php
	require("../mysql.php");

	$text = $_GET['text'];
	$user = $_GET['user'];
	$date = date("Y-m-j H:i:s");

	if($text!="")
	{
		mysql_query("INSERT INTO tab_muell (user, msg, time) VALUES ('$user', '$text', '$date')")
			or die("Fehler: " . mysql_error());
	}
?>
