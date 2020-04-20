<?php
     // create a PHP object with the filename,filetype, and cwd properties.
     
     
  $json = $_REQUEST["json"];  
  echo $json; 
	$myfile = fopen("assign13.txt", "w") or die("Unable to open file!");
   fwrite($myfile, $json); 
   fclose($myfile);
   

 
 ?>
