function start()
{
   var colorr = document.getElementById("colorr").value;
   $("#first").css({"color": colorr});
}


function fade(){
    $('.third').delay(0).fadeOut(5000);
}