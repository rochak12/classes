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
  text-align:left;
}

.box{
margin-top: 0;
width:90%;
margin-right: 20%;
font-size: 14pt;
}

pre{
font-size:14pt;
margin: 0pt;
}

</style>
 </head>
 
 <body style="background-image:url(back.jpg)">
 <div class="box">
   <h1>Confirm your purchase<h1>
  <?php
		$firstname = $_GET['firstname'];
		$lastname = $_GET['lastname'];
		$address = $_GET['address'];
		$phone = $_GET['phone'];

		$card = $_GET['money'];
		$cnumber = $_GET['cnumber'];
		$expdate = $_GET['expdate'];


		print "<form action='assign11_a.php' method='get' >
       <p>Name: $firstname $lastname </p>
	     <p>Address: $address  </p>
	     <p>Phone: $phone </p>";
	     
    if(isset($_GET['c'])) {
    $item = $_GET['c'];

    echo "<p>You chose the following items: </p>";    
    foreach ($item as $c)
   { 
   if ($c == 25.00)
       echo "<pre>     Flower:               $c </pre>";
   if ($c == 22.00)
       echo "<pre>     Wind Chime:           $c </pre>";
   if ($c == 50.00)
       echo "<pre>     choclate gift:        $c </pre>";
   if ($c == 22.56)
       echo "<pre>     Nudge:                $c </pre>";
   if ($c == 16.00)
       echo "<pre>     Elon Musk:            $c </pre>";
   if ($c == 15.50)
       echo "<pre>     Think fast and slow:  $c </pre>";               
       }
    }
     else
         echo"<pre>     You didn't choose any item. </pre>";     
     
     
       foreach ($item as $c)
       {
       $total += $c;
        } 
          
   print "<p>Total: $total </p>
       <p>card: $card</p>";
       
       
       
       
       
       
       
       
       $dates = explode('/', $expdate);
       $monthName = date('F', mktime(0, 0, 0, $dates[0], 10));
 print "<p>Expiration date: $monthName";
 echo  ' 20' . $dates[1];
 
 
       echo"</p>
       <button type='submit' name='confirm' value='confirm'>Confirm</button>
		   <button type='submit' name='confirm' value='cancel'>Cancel</button>
 
	   </form>";

    ?>



    </div>

	</body>
