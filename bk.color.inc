<?php
include_once('bk.save.inc');
function bk_page_colors(){
////////////////////////////////////////////////  précautions
$color_safe = db_result(db_query("SELECT count(*) from {bk_options} where id = '%s'",'range'));
if ( !$color_safe) {

db_query("INSERT INTO {bk_options} (bk_id,    id,       data ,      color) 
					                      VALUES (0,    'range',         '0' ,       'B3BFBF')");
db_query("INSERT INTO {bk_options} (bk_id,    id,       data ,      color) 
					                      VALUES (1,    'range',         '1' ,       '628220')");
db_query("INSERT INTO {bk_options} (bk_id,    id,       data ,      color) 
					                      VALUES (2,    'range',         '2' ,       'F99C4F')");
db_query("INSERT INTO {bk_options} (bk_id,    id,       data ,      color) 
					                      VALUES (3,    'range',         3 ,       'FFFF00')");										  
$reglage = 10;

for ($i = 4 ; $i <= 4+$reglage ; $i++) {

                                      db_query("INSERT INTO {bk_options} (bk_id,    id,       data ,      color) 
					                      VALUES (%d,    'range',         '%s' ,       '')", 
					                       $i,  (string)$i);

                              }



                     }
////////////////////////////////////////////////  debut de la page couleurs
$out =  '';

$admod = drupal_get_path('module','bk');
drupal_add_js($admod.'/js/colorpicker.js');
drupal_add_js($admod.'/js/eye.js');
drupal_add_js($admod.'/js/utils.js');
drupal_add_js($admod.'/js/layout.js');
drupal_add_css($admod.'/css/colorpicker.css');
drupal_add_js($admod.'/js/bk.js');

$out .= '<a href="/admin/bk">Coutries</a>&nbsp;&nbsp;&nbsp;||&nbsp;&nbsp;&nbsp;<a href="/Country-Activities" target="_blank">map</a><br>';
$out .=  'actual colors :<br>';
$out .= '<hr>set a country to <b>data 0 </b> or empty and it wont appear in map or countrylist. <br>';
$color_query = db_query("SELECT * FROM {bk_options} ORDER BY bk_id ASC");


$yyy =  db_result(db_query("SELECT count(*) FROM {bk_options}"));
$resx_color = (int)$yyy-1;

//drupal_set_message($resx_color);
while ($opt = db_fetch_object($color_query)) 
   { 
 if ($opt->data !== '0') {
 
                         if (($opt->bk_id > 5) && ($opt->bk_id == $resx_color))
						       {$del_xt = '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="#" class="deletcolor" del="'.$opt->bk_id.'"><img src="/'.$admod.'/delete.gif"></a>';} 
                           else {$del_xt = '';}
						 
    $out .= '<hr><div><font color="#'.$opt->color.'">data '.$opt->data.' is set at '.$opt->color.'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <a href="/admin/bk/options/modify/'.$opt->bk_id.'">modify '.$opt->color.'</a></font>'.$del_xt.'</div>';
                         }
    }
$out .= '<a href="#" id="createcolor">new color</a>'.'<br>';
return $out;
}

function bk_createcolor() {

$nx = db_result(db_query( "SELECT count(*) FROM {bk_options}"));
$nb_co = (int)$nx ;
$ins_query = db_query("INSERT INTO {bk_options} ( bk_id, id ,  data, color) 
					   VALUES (%d ,'%s','%s','%s')", 
					  $nb_co ,'range',(string)$nb_co,'00FF00');
					  
$tab_retur = array('result' => $ins_query);

drupal_json($tab_retur);
exit();
}

function bk_deletecolor($argx) {
if($argx > 5) {

 $race = db_query("DELETE FROM {bk_options} WHERE bk_id = %d", $argx); 
$col = db_query("UPDATE {bk} SET `data` = '%s'  WHERE data = '%s'",'0', (string)$argx);  
bk_global_save();
		       }


$tab_retur = array('result' => $race);
drupal_json($tab_retur);
exit();
}

function bk_color_modify_form($form_state,$variable){
$path= drupal_get_path('module','bk');
drupal_add_js($path.'/js/jquery.js');
drupal_add_js($path.'/js/colorpicker.js');
drupal_add_js($path.'/js/eye.js');
drupal_add_js($path.'/js/utils.js');
drupal_add_js($path.'/js/layout.js');
drupal_add_js($path.'/js/bk.js');
drupal_add_css($path.'/css/colorpicker.css');

$color_modify = db_query("SELECT * from {bk_options} where bk_id = %d",$variable);
 while ($options = db_fetch_object($color_modify)) { 

$color = $options->color;
 }
$bgcolor = '#'.$color;
 
 $form = array();
 $form['tutux'] = array(
    	'#value' => '<div align="middle"> <a href="/admin/bk"> Countries settings</a></div>',
		);
$form['fieldset'] = array(
    	'#type' => 'fieldset',
    	'#title' => 'modifiy color '.$variable,
    	'#collapsible' => TRUE,
    	'#collapsed' => FALSE,
		);
		
	 $form['fieldset']['color'] = array(
    '#type' => 'textfield',
    '#title' => 'data '.$variable,
	'#default_value' =>  strtoupper($color),
    '#required' => False,
     ); 
	$form['fieldset']['markup'] = array(
	 '#type' => 'textfield',
	 '#default_value' =>  $color,
	 '#size' => 7,
	 '#prefix' => '<div id="colorSelector"style="width:120px;" >',
	  '#suffix'  => '</div>',
	  '#value' =>  'Selector',
	  '#attributes' => array( 'style' => 'bgcolor="'.$bgcolor.'"' ),
	  );
     $form['fieldset']['hidden'] = array('#type' => 'value', '#value' =>$variable);
     $form['fieldset']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('set color'),
	   '#prefix' => '<div >',
	    '#suffix'  => '</div>',
      );	
	  $form['retour'] = array(

	 '#prefix' => '<a href="/admin/bk/options">',
	  '#suffix'  => '</a>',
	  '#value' =>  'exit without saving',
	  '#attributes' => array( 'style' => 'float="middle"' ),
	  );
return $form;


}



function bk_color_modify_form_validate($form, &$form_state) {
  if ($form_state['values']['color'] == 'tutu') {
    //form_set_error('', t('You must select a DATA for this group of settings.'));
  }
}
function bk_color_modify_form_submit($form, &$form_state) {

  db_query("UPDATE {bk_options} SET `color` = '%s' where bk_id = %d", strtoupper($form_state['values']['color']), $form_state['values']['hidden']);
  drupal_set_message($form_state['values']['color'].' settings has been saved in data '.$form_state['values']['hidden']);
 bk_global_save();
   drupal_goto('admin/bk/options');
}


function bk_get_color($bk_id) {
$color = '';
$color_ask = db_query("SELECT * from {bk_options} where bk_id = %d",$bk_id);
 while ($options = db_fetch_object($color_ask)) { 
$color .= $options->color;

 }
return $color;
}












