<?php
	header('Content-Type: text/html; charset=latin1');

	require("../mysql.php");


	$query = "SELECT * FROM tab_muell ORDER BY time DESC";
	$result = mysql_query($query)
		or die("Anfrage fehlgeschlagen: " . mysql_error());

	$last = 0;
		
	while ($line = mysql_fetch_array($result, MYSQL_NUM))
	{
		echo "<u>$line[0]:</u> <br><i>$line[1]</i><br><br>";
		$last = $line[2];
	}	

	if(mysql_num_rows($result) > 8)
	{
		$query = "DELETE FROM tab_muell WHERE time='$last'";
		
		$result = mysql_query($query)
			or die("Anfrage fehlgeschlagen: " . mysql_error());
	}
?>
