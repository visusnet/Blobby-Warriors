function getContent(content)
{
	if(content == content_old)
		return;
		
	$.ajax(
	{
		type: "GET",
          	url: "php/content.php",
           	data: "site="+content,
           	async: false,
           	success: function(msg)
		{
			$("div#navigation > ul > li > a").removeClass("active");

			if(content_old == "play")
			{
				$("div#leftBig").show("slow");
				$("div#rightBig").show("slow");

                       		$("div#content").fadeOut("slow", function()
				{
					$("div#content").html(msg).show("slow");
				});
			}
			else
			{
				$("div#content").hide("slow", function()
				{
					if(content == "play")
					{		
						$("div#leftBig").hide("slow");
						$("div#rightBig").hide("slow");

						$("div#content").html(msg).fadeIn("slow");
					}
					else
						$("div#content").html(msg).show("slow");
				});
			}


                        $("a#"+content).addClass("active");
			content_old = content;
		}
    });
}


function refreshUserOnline()
{
	$.ajax(
	{
		type: "GET",
          	url: "php/useronline.php",
           	data: "",
           	async: false,
           	success: function(msg)
		{
			$("div#useronline_body").html(msg).fadeIn("slow");
		}
	 });

}


function refreshMuellomat()
{
	$.ajax(
	{
		type: "GET",
          	url: "php/mom/read.php",
           	data: "",
           	async: false,
           	success: function(msg)
		{
			$("div#muell_body").html(msg).fadeIn("slow");
		}
	 });
}


function writeMuellomat(text)
{
	if(username == "")
	{
		alert("Du musst angemeldet und eingeloggt sein um in den Müllomat schreiben zu können.");
		return;
	}

	$.ajax(
	{
		type: "GET",
          	url: "php/mom/write.php",
           	data: "user="+username+"&text="+text,
           	async: false
	 });
}

function updateAccountBody()
{
	if(username != "")
	{
		// neuen account-body createn
		document.getElementById('account_body').innerHTML="<b>"+username+"</b><br><br>";
		document.getElementById('account_body').innerHTML+="<u> Profil </u><br>";
		document.getElementById('account_body').innerHTML+="<u> Statistik </u><br>";
		document.getElementById('account_body').innerHTML+="<u> Nachrichten </u><br><br>";
		document.getElementById('account_body').innerHTML+="<a href='#' onclick='runLogout();'> <i> ausloggen </i> </a><br>";
	}
	else
	{
		document.getElementById('account_body').innerHTML="<a href='#' onclick='getContent(\"login\")'> einloggen </a><br>";
		document.getElementById('account_body').innerHTML+="<a href='#' onclick='getContent(\"register\")'> registrieren </a>";
	}
}

function runLogout()
{
	username = "";

	getContent("news");

	updateAccountBody();
}




function timer_update() 
{
	sayHello();
	updateAccountBody();
	refreshUserOnline();
	refreshMuellomat();
}

function sayHello()
{
	if(username == "")
		return;

	$.ajax(
	{
		type: "GET",
          	url: "php/online.php",
           	data: "user="+username,
           	async: false
	 });
}

function runRegister()
{
	alert(document.getElementById('muell_text').innerHTML);

	/*var user = document.getElementById("register_user").value;
	var pass = document.getElementById("register_pass").value;
	var pass2 = document.getElementById("register_pass2").value;


	alert(user + " " + pass + " " + pass2);*/

}


function runLogin(user, pass)
{
    if(user=="" || pass=="")
    {
    	alert("Bitte das Formular richtig ausfüllen!");
    }
    else
    {
    	$.ajax({
           	type: "GET",
           	url: "php/login.php",
           	data: "user="+user+"&pass="+pass,
           	success: function(msg)
                    {
			if(msg==0)
			{
				document.getElementById('login_user').value="";
				document.getElementById('login_pass').value="";
				username = user;

				timer_update();

				getContent("news");
			}
			else if(msg==2)
			{
				alert("Username falsch.");
				document.getElementById('login_user').value="";
				document.getElementById('login_pass').value="";
			}
			else if(msg==3)
			{
				alert("Passwort falsch.");
				document.getElementById('login_pass').value="";
			}
			else
			{
				alert("Serverseitiger Fehler. Bitte dem Admin melden.");
				document.getElementById('login_user').value="";
				document.getElementById('login_pass').value="";
			}
                    }
           	});
    }
}



function runContact(from,subject,msg)
{
    if(from=="" || subject=="" || msg=="")
    {
    	alert("Bitte das Formular richtig ausfüllen!");
    }
    else
    {
    	$.ajax({
           	type: "GET",
           	url: "php/contact.php",
           	data: "text="+msg+"&subject="+subject+"&from="+from,
           	success: function(msg)
                    {
			alert(msg);

			document.getElementById('contact_subject').value="";
			document.getElementById('contact_text').value="";
                    }
           	});
    }
}


$(document).ready(function()
{
	getContent('news');

	$("div#navigation > ul > li > a").click(function()
	{
		getContent(this.id);
	});

	timer_update();

	setInterval('timer_update()',5000);
});
