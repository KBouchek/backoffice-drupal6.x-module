<?php
//$Id$

function bk_admin_settings() {


$form['fieldset'] = array(
    	'#type' => 'fieldset',
    	'#title' => t('settings'),
    	'#collapsible' => TRUE,
    	'#collapsed' => FALSE,
		);
		

	 $form['fieldset']['node_effect'] = array(
    '#type' => 'select',
    '#title' => t('Enable refresh button'),
	 '#options' => array( TRUE => 'Enable', FALSE => 'Disable' ),
	'#default_value' =>  variable_get('node_effect',  array(TRUE => 'Enable')),
	'#description' => 'If Enable , administrators will see a refresh link on map countries.<br>empty navigator\'s cache for permanent fresh data',
    '#required' => TRUE,
     ); 
/*	 
	 $form['fieldset']['text'] = array(
    '#type' => 'textarea',
    '#title' => t('Text on nodes results'),
	'#default_value' =>  variable_get('text', ''),
	'#rows' => 3,
	'#resizable' => TRUE,
	'#description' => 'This text, if non empty, will be displayed fist on all results pages.<br>You can use html tags',
    '#required' => False,
     ); 
	 
	  $form['fieldset']['padding'] = array(
    '#type' => 'textfield',
    '#title' => t('Message padding bottom '),
	'#descriton' => 'in going to be in pixels. Enter something like 5 , just a number.',
	'#default_value' =>  variable_get('padding', '15'),
    '#required' => TRUE,
     ); 
*/
$form['exit'] = array(
    	'#value' => '<center><a href="/admin/bk">back to countries settings</a></center>',
		);
return system_settings_form($form);

}	

function bk_admin_settings_validate() {

//drupal_set_message('yeah','error');
//drupal_goto('/admin/bk');
}

