Drupal.behaviors.getcountry = function (context) {
		//attach click event handlers to links
		$('#countries').bind("change", function(){
		flashProxy.call('zoomOut');
				if ( $(this).val()==''){return false;}										 
				getcountry_country( $(this).val() );
				//return false;
		});

	};
$(document).ready(function(){
   $("a#dezoom").click(function(event){
     flashProxy.call('zoomOut');
	 //alert("dezomm");
   });
 });

/*
$('#dezoom').bind("click", function(e){
	e.preventDefault();
		flashProxy.call('zoomOut');
		//e.preventDefault();
				//if ( $(this).val()==''){return false;}										 
				//getcountry_country( $(this).val() );
				//return false;
		});
*/
function getcountry_country(country){
if (country == "") {return false;}
var tab = country.split("/");
var requete = tab[0];

//if($.browser.msie && $.browser.version=="5.5") {alert("Im the annoying IE5");}
//if($.browser.msie && $.browser.version=="6.0") {alert("Im the annoying IE6");}
if (requete == "http:") {

     var content = '';
	 content+= '<center><div style="margin:0;"><img style="margin:0" alt="" src="/sites/default/files/bandeaup21.jpg" width="450" height="65"><div>';
	 content+= '<center><h3>You are exiting PARIS21 Web Server <br>Thank you for visiting our site.</center></h3>';
	 content+= '<center><hr></center>';
	 content+= '<center><div><h4>To keep a window open on PARIS21.org, please click on the link below</h4></div></center>';
     content+= '<center><div><a id="remove" href="'+country+'" target="_blank">'+country+'</a></div></center>';
     content+= '';
	
$.nyroModalManual({
                     width: 450,
                     height: 260,
                   bgColor: '#F6F6F6',
                  content: content 
                    });
/////////////////// si le lien est cliqué , l'utilisateur reste	sur le site						
$("a#remove").click(function() {
                                //stay = true;
                                $.nyroModalRemove();
                                
});	
/////////////////// si la fenetre modale n'a disparue						
setTimeout(function(){
				   var opa = $("#remove").width();
				   if (opa != null) {
				   $(location).attr('href',country);
				                    }
                         },5000);					

}

else {$(location).attr('href',country); }

}
