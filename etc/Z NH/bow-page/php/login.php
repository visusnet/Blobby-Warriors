<?php
	require("mysql.php");


	$user=$_GET['user'];
	$pass=$_GET['pass'];

	$query = "SELECT * FROM tab_user WHERE username='$user';";

	$result = mysql_query($query)
		or die("1");


	if(mysql_num_rows($result) <= 0)
	{
		print("2");
		return;
	}


	$line = mysql_fetch_array($result, MYSQL_NUM);
	if($line[1] == $pass)
	{
		print("0");
	}
	else
	{
		printf("3");
	}
?>
