	<!docHTML>
 <head>
 <meta content="text/html;charset=utf-8" http-equiv="Content-Type">
	<title>Server side form processing using PHP</title>
	<link rel=StyleSheet type="text/css" href="style.css" />

<style>
body {
text-align :center;
}


form {
	width: 90%;
	background-color: #f2f2f2;
  margin-right:20%;
  margin-left : 1%;
}

.box{
width:90%;
margin-right: 20%;
font-size: 24pt;
}

</style>
 </head>
 
 <body style="background-image:url(back.jpg)">
 <div class="box">

  <?php
	$confirm = $_REQUEST['confirm'];
  if ($confirm == 'confirm')
   echo "<p> Purchase successful</p>";
   else
   echo "<p> Purchase Canceled </p>";
 
 
 

    ?>
    </div>
	</body>

