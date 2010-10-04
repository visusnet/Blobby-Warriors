<?php
	header('Content-Type: text/html; charset=latin1');

	require("mysql.php");


	$type = $_GET['type'];

	$query = "SELECT * FROM tab_content WHERE type = '$type' ORDER BY time DESC";
	$result = mysql_query($query)
		or die("Anfrage fehlgeschlagen: " . mysql_error());

		
	while ($line = mysql_fetch_array($result, MYSQL_NUM))
	{
		echo $line[2];
	}
?>
