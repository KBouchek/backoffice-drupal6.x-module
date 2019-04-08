Drupal.behaviors.bk = function(context) {

$('.deletcolor').bind("click", function(){
   //evt.preventDefault();
   var urldel = "/admin/bk/options/deletecolor/"+$(this).attr('del');
var answer = confirm("Delete selected color ? All countries shall be reset to color 0")
    if (answer){
        
   $.ajax({	
							          url: urldel,
							          type: "GET",
							         dataType: "json",
							          success: function(jsony){  
									                            
																  location.href="/admin/bk/options";
																  
  
                                                                }
																
         });
		 }
	
	else {}
 	 
   
 });

$('#createcolor').click(function() {

//alert("ok");
 //ev.preventDefault(); 
 //var nb = $(this).attr('nb');

 var urlcreation = "/admin/bk/options/createcolor";
//alert(urlcreation);
  $.ajax({	
							          url: urlcreation,
							          type: "GET",
							         dataType: "json",
							          success: function(jsonx){
                                                                   if(jsonx.result) {location.href="/admin/bk/options";}
																   else {alert("a problem occured during color creation");location.href="/admin/bk/options";}
  
                                                                }
															
         });
  
});

$('#xmr').click(function (e) {
 e.preventDefault();  
                                                        	 
  							 $.ajax({	
							          url: "/admin/bk/give/regions",
							          type: "GET",
							         dataType: "json",
							          success: function(json){
									  
									   //alert("ok");
									var id = $(this).attr('href');
									 var tutu = json.texte;
									 
	                                                           //var maskHeight = $(document).height();
															    var maskWidth = $(window).width(); 
																//alert(maskWidth);
																$('#mask').css({'width':800,color:'red'});
																//,'height':maskHeight
																//transition effect
																 $('#mask').fadeIn(1000);
																 //$('#mask').fadeTo("slow",0.8);
																  //Get the window height and width
																   var winH = $(window).height();
																    var winW = $(window).width();
																	//Set the popup window to center
																	$(id).css('top', winH/2-$(id).height()/2);
																	$(id).css('left', winW/2-$(id).width()/2);
																	//transition effect
																		$('#mask').html(tutu);
																	$(id).fadeIn(1000); 	
																
									  
									 $('#mask').click(function () {  
									 	$('#mask').html('');
                                                                $(this).hide();  
                                                                  $('.window').hide();  
                                                                   }); 
									  
									  
									  
									  
                                                             //alert(text);
															 //var dd = flash_go(json.country,json.data);
															//alert (json.regionupdate);
															 //															 location.href="/admin/flash";
															 //flash_get_rep(json.country);
			                                                 
                                                               }
									});
  

  
  
});

$('#xml').click(function (e) {
 e.preventDefault();  
                                                        	 
  							 $.ajax({	
							          url: "/admin/bk/give/countries",
							          type: "GET",
							         dataType: "json",
							          success: function(json){
									  
									   //alert("ok");
									var id = $(this).attr('href');
									 var tutu = json.texte;
									 
	                                                           //var maskHeight = $(document).height();
															    var maskWidth = $(window).width(); 
																//alert(maskWidth);
																$('#mask').css({'width':600,color:'red'});
																//,'height':maskHeight
																//transition effect
																 $('#mask').fadeIn(1000);
																 //$('#mask').fadeTo("slow",0.8);
																  //Get the window height and width
																   var winH = $(window).height();
																    var winW = $(window).width();
																	//Set the popup window to center
																	$(id).css('top', winH/2-$(id).height()/2);
																	$(id).css('left', winW/2-$(id).width()/2);
																	//transition effect
																		$('#mask').html(tutu);
																	$(id).fadeIn(1000); 	
																
									  
									 $('#mask').click(function () {  
									 	$('#mask').html('');
                                                                $(this).hide();  
                                                                  $('.window').hide();  
                                                                   }); 
									  
									  
									  
									  
                                                             //alert(text);
															 //var dd = flash_go(json.country,json.data);
															//alert (json.regionupdate);
															 //															 location.href="/admin/flash";
															 //flash_get_rep(json.country);
			                                                 
                                                               }
									});
  

  
  
});



 
  $('#colorSelector').ColorPicker({
	color: '#0000ff',
	onShow: function (colpkr) {
		$(colpkr).fadeIn(500);
		return false;
	},
	onHide: function (colpkr) {
		$(colpkr).fadeOut(500);
		return false;
	},
	onChange: function (hsb, hex, rgb) {
		$('#colorSelector div').css('backgroundColor', '#' + hex);
	}
});




  }
  
