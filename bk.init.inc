<?php

function bk_initialize() {


$output_tab = array();
$retour = array();
$path = drupal_get_path('module','bk');
$name_file = $path.'/../../../map/world/data.xml';
//$name_file = './sites/map/world/data.xml';
$out = '';
$ligne = 0;
if (is_file($name_file) && $handle = fopen($name_file, "r"))
{
while (!feof($handle)) {
	$ligne++;
  $out .= fread($handle, 35024);
}
fclose($handle);
		}
else {drupal_set_message("can not open file map/world/data.xml","error");}
$tab = explode('state id="',$out);
$count = count($tab);

/////////////////////////////////  Reccup de tous les id et noms que la carte pourra ultérieurement utiliser  /////////////////
$record = array();
$ligne_counter = 0;
$ligne_counterx = 0;
foreach($tab as $cle => $state)
{

$init_handle = explode("\"",$state);
$id = $init_handle[0];


if ($id == 'range') {

                        bk_set_color($ligne_counter,$state);
						$ligne_counter++;
						}
						
						
if (strlen($id) == 2) {
$ligne_counterx++;
                         bk_set_country($ligne_counterx,$id,$state);
                        //echo $cle.'<br>';
                       ////bk_set_color($state);
					   }

 			   
	
	}
}


function bk_set_country($m,$idx,$line) {

$ex0 = explode("name>",$line);
$name  = strip_tags($ex0[1]);

$ex1 = explode("data>",$line);
$data  = strip_tags($ex1[1]);

$ex2 = explode("url>",$line);
$url  = strip_tags($ex2[1]);

$ex3 = explode("target>",$line);
$target  = strip_tags($ex3[1]);

//////////////////////////////////////recherche du term et du nid associé

$sub = substr($url, 0, 4);
if ( $sub == 'http' || $url == '') {
$term = ''; $nid_res = '';
}
else {

$ex = explode("/",$url);
$term = $ex[2];
$sqlz = "SELECT * FROM {term_data} AS d INNER JOIN {term_node} AS n ON d.tid = n.tid WHERE d.name  = '%s'";
$anciens = db_query($sqlz,$term );
$nid_res = '';
while ($datax = db_fetch_object($anciens)) {  $nid_res = $datax->nid ; }

}
//////////////////////////////////////insertion en base

$y = db_query("INSERT INTO {bk} ( bk_id, id ,  name,  data, url ,target ,term,nid) 
					   VALUES (%d ,'%s','%s','%s','%s','%s','%s',%d)", 
					  $m ,$idx,$name,$data,$url,$target,$term,$nid_res);
					  
}

function bk_set_color($n,$line) {

$ex1 = explode("data>",$line);
$data  = strip_tags($ex1[1]);

$ex2 = explode("color>",$line);
$color  = strip_tags($ex2[1]);

$y = db_query("INSERT INTO {bk_options} ( bk_id , id ,  data , color ) 
					     VALUES (%d ,   '%s',   '%s' ,   '%s')", 
					           $n, 'range' ,$data, $color);
										
}


