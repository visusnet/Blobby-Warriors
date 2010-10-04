<?php
header('Content-Type: text/html; charset=latin1');
if (isset($_REQUEST['site']) && !empty($_REQUEST['site'])
 && !preg_match("/\./", $_REQUEST['site'])
 && file_exists("../content/".$_REQUEST['site'].".tpl"))
        print(file_get_contents("../content/".$_REQUEST['site'].".tpl"));
else
    print(file_get_contents("../content/error404.tpl"));

?>