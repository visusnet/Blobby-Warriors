<?php
	require("mysql.php");


	$time = time() - 10;

	$query = "SELECT * FROM tab_user WHERE lastSeen > '$time'";

	$result = mysql_query($query)
		or die("error");


	if(mysql_num_rows($result) <= 0)
	{
		echo "<i>keine user online</i>";
		return;
	}

	while ($line = mysql_fetch_array($result, MYSQL_NUM))
	{
		echo $line[0] ."<br>";
	}
?>
