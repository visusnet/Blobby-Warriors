function getContent(content)
{
    $.ajax({
           type: "GET",
           url: "content/test.txt",
           data: "site="+content,
           async: false,
           success: function(msg)
                    {
                        $("div#navigation > ul > li > a").removeClass("active");
                        $("div#content").hide("slow", function()
                                                      {
                                                          $("div#content").html(msg).show("slow");
                                                      });
                        $("a#"+content).addClass("active");
                    }
           });
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
           	url: "contact.php",
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

                  });
