<?php

$text=$_GET['text'];
$subject=$_GET['subject'];
$from=$_GET['from'];

$mail = array(
              "TO"      => "info@bow.crav3x.net",
              "FROM"    => $from,
              "SUBJECT" => $subject,
              "TEXT"    => $text
              );

if (mail($mail['TO'], $mail['SUBJECT'], $mail['TEXT'], "From: ".$mail['FROM']))
    print("Erfolgreich gesendet!");
else
    print("Es trat ein Fehler bei dem Senden auf!");
?>
