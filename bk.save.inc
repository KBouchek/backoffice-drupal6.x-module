<?php

function bk_global_save(){
 
 /////////////////////////////////////////////////////
$out = '';
$out .= '<countrydata>';
$resultat = '';
$req_options = db_query("SELECT * FROM {bk_options} where id = '%s' ORDER BY bk_id ASC", 'range');  
$out_options = '';
while ($row = db_fetch_object($req_options)) { 
      if ($row->data !== '' && $row->color !== '') {
$out_options  .= '
<state id="range">
<data>'.$row->data.'</data>
<color>'.$row->color.'</color>
</state>';
                                                    }
                                                }
												
$out .= str_replace("
","\n",$out_options);
////////////////////////////////////////////
$mod ='
<state id="default_color">
<color>bbbbbb</color>
</state>
<state id="background_color">
<color>EFEFEF</color>
</state>
<state id="outline_color">
<color>666666</color>
</state>
<state id="default_point">
<color>333333</color>
<size>5</size>
<opacity>100</opacity>
</state>
<state id="first_zoom">
</state>
<state id="zoom_mode">
</state>
<state id="zoom_out_center">
</state>
<state id="zoom_out_scale">
<data>100</data>
</state>
';
$out .= str_replace("
","\n",$mod);
////////////////////////////////////////////////
$resultat = '';
$req = db_query("SELECT * FROM {bk}");  
while ($row = db_fetch_object($req)) {
 if ( $row->data !== '0' && $row->data !== '' && $row->url !== '') {
$resultat .= '<state id="'.$row->id.'">
';
if ($row->name !== '') 
{$resultat .= '<name>'.$row->name.'</name>
';}
if ($row->data !== '') 
{$resultat .= '<data>'.$row->data.'</data>
';}
if ($row->url !== '') 
{
//$resultat .= '<url>javascript:getcountry_country("'.$row->url.'");</url>';
}
$resultat .= '</state>
';
}
}
/////////////////////////////////////javascript:adp_diymap_get_country("Argentina")
$out .= str_replace("
","\n",$resultat);
$out .= '</countrydata>';

$path_country = drupal_get_path('module','bk');
$name_file = $path_country.'/data.xml';

$handle = fopen($name_file, "w+");  
$res_w = fwrite ( $handle , $out);
fclose($handle);

$nodex = bk_get_html();
$node_r = db_result(db_query("SELECT vid FROM {node} WHERE nid = %d ", 37)); 
$db_x = db_query("UPDATE {node_revisions} SET `body` = '%s' WHERE vid = %d", $nodex , $node_r); 

return drupal_set_message('data.xml : '.$res_w.' octets and update node 37 : '.$db_x);
}


function bk_get_html() {

$body = '';
$body .= '<script type="text/javascript" src="'.drupal_get_path('module','bk').'/js/jquery.nyroModal-1.6.2.js"></script>';
$body .= '<link rel="stylesheet" href="'.drupal_get_path('module','bk').'/css/nyroModal.css" type="text/css" media="screen" />';
$body .='<script type="text/javascript" src="../sites/map-region/world/with_javascript/js/JavaScriptFlashGateway.js">
</script>

<script type="text/javascript" src="../sites/all/modules/flash/map/world/with_javascript/js/JavaScriptFlashGateway.js"></script>
<script type="text/javascript" src="../sites/all/modules/flash/map/world/with_javascript/js/Exception.js"></script>
<script type="text/javascript" src="../sites/all/modules/flash/map/world/with_javascript/js/FlashTag.js"></script>
<script type="text/javascript" src="../sites/all/modules/flash/map/world/with_javascript/js/FlashSerializer.js"></script>
<script type="text/javascript" src="../sites/all/modules/flash/map/world/with_javascript/js/FlashProxy.js"></script>

<div>
<script type="text/javascript">
var uid = new Date().getTime();
var flashProxy = new FlashProxy(uid,"../sites/all/modules/flash/map/world/with_javascript/js/JavaScriptFlashGateway.swf");
var tag = new FlashTag("../sites/all/modules/flash/map/world/world.swf?data_file=../sites/all/modules/bk/data.xml", 700, 300);
tag.setFlashvars("lcId="+uid);
tag.write(document);
</script></div>

<script type="text/javascript">
function getcountry_country(arg) {
/*
var tab = arg.split("/");
var requete = tab[0];
//alert(requete);
if (requete == "http:") {window.open(arg);}
else {document.location.href=".."+arg;}	
*/
}
</script>'
;

/*
$body .= '
<script type="text/javascript" src="../sites/all/modules/bk/map/world/with_javascript/js/JavaScriptFlashGateway.js">
</script>
<script type="text/javascript" src="../sites/all/modules/bk/map/world/with_javascript/js/Exception.js">
</script>
<script type="text/javascript" src="../sites/all/modules/bk/map/world/with_javascript/js/FlashTag.js">
</script>
<script type="text/javascript" src="../sites/all/modules/bk/map/world/with_javascript/js/FlashSerializer.js">
</script>
<script type="text/javascript" src="../sites/all/modules/bk/map/world/with_javascript/js/FlashProxy.js">
</script> 
<script type="text/javascript">
var uid = new Date().getTime();
var flashProxy = new FlashProxy(uid,"../sites/all/modules/bk/map/world/with_javascript/js/JavaScriptFlashGateway.swf");
var tag = new FlashTag("../sites/all/modules/bk/map/world/world.swf?data_file=../sites/all/modules/bk/data.xml", 700, 300); 
tag.setFlashvars("lcId="+uid);
tag.write(document);
</script>';
*/
$body .= '
<table border="0" style="width: 700px;">
<tr ><td width = "350"><center>
<select name="countries" id="countries"><option value="" >Select Country</option>';
$query = db_query("SELECT * FROM {bk} ORDER BY name ASC");  
while ($opx = db_fetch_object($query)) {
if (  $opx->data !== '' && $opx->data !== '0' ) {
         $body .= '<option value="'.$opx->url.'">'.$opx->name.'</option>' ; 
		                                         }
                                        }
$body .= '</select></center></td>';
$body .= '<td width="350px" style="vertical-align:middle">
<center><a href="javascript:flashProxy.call(\'zoomOut\');" id="dezoom">Zoom Out</a></center></td>
</tr></table>';



return $body ;

}


