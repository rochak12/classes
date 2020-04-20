	<!docHTML>
 <head>
 <meta content="text/html;charset=utf-8" http-equiv="Content-Type">
	<title>assignment 6</title>
	<link rel=StyleSheet type="text/css" href="style.css" />

<style>
body {
text-align :center;
}

.box{
padding: 20px;
font-size: 24pt;
}

</style>
 </head>
 
 <body style="background-image:url(back.jpg)">
  <br/> <br/>
 <div class="box">

  <?php
		$apr = $_REQUEST["aprate"];
		$lterm = $_REQUEST["lterm"];
		$lamount = $_REQUEST["lamount"];
		
		echo("Annual Percentage Rate: " . $apr);
		echo("<br/><br/>Loan Term: " . $lterm);
		echo("<br/><br/>Loan Amount: " . $lamount);
    
		$c = ($apr / 100) / 12;
		$poww = pow((1 + $c), $lterm * 12);
		$mpayment = $lamount * $c * $poww / ($poww - 1);
		echo("</br><br/><hr/> Monthly Payment: ");
		echo number_format((float)$mpayment, 2, '.', '');
	
	    

    ?>
    </div>
    </body>
