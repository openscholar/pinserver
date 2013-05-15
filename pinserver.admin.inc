<?php

//@file pinserver.admin.inc

/**
 * pinserver_config()
 *
 * @return array - returns form for pinserver administrative settings
 */
function pinserver_config(){
  global $base_url;

  $form['pinserver'] = array(
  '#type' => 'fieldset',
  '#title' => t('Harvard Pinserver Configuration'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );

  $form['pinserver']['pinserver_pin_url'] = array(
  '#type' => 'textfield',
  '#required' => TRUE,
  '#title' => t('Harvard PIN Server URL'),
  '#default_value' => variable_get('pinserver_pin_url',''),
  '#description' => t('Enter Pin server URL. For example: https://www.pin1.harvard.edu/pin/authenticate'),
  );

  $form['pinserver']['pinserver_app_name'] = array(
  '#type' => 'textfield',
  '#title' => t('Harvard PIN server application name'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_app_name',''),
  '#description' => t('Enter the application name given to you by Harvard Directory Services.' ),
  );

  $form['pinserver']['pinserver_gpg_dir'] = array(
  '#type' => 'textfield',
  '#title' => t('Host server path to public key directory'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_gpg_dir',''),
  '#description' => t('Enter the absolute path to the GPG directory on your web server where the PIN Server or AuthProxy public key information is stored.' ),
  );

  $form['pinserver']['pinserver_landing_path'] = array(
  '#type' => 'textfield',
  '#title' => t('Landing Path'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_landing_path',''),
  '#description' => t('Specify the path to redirect the user after all pinserver module processing is complete. Use a relative path that comes after !base_url' .'/', array('!base_url' =>$base_url)),
  );

  $form['pinserver']['pinserver_auth_str'] = array(
  '#type' => 'radios',
  '#title' => t('PIN Authentication Server Setup'),
  '#default_value' => variable_get('pinserver_auth_str', ''),
  '#options' => array(
  'Good signature from "Harvard University PIN System' => t('PIN only'),
  'Good signature from "authzproxy"' => t('PIN with AuthProxy'),
  ),
  '#required' => TRUE,
  '#description' => t('The server that is returning the user back to this site after successful PIN login.'),
  );

  $form['pinserver']['pinserver_support_contact'] = array(
  '#type' => 'textfield',
  '#title' => t('E-mail address for techincal support'),
  '#required' => FALSE,
  '#default_value' => variable_get('pinserver_support_contact',''),
  '#description' => t('Optionally specify contact person to be displayed to user if PIN authentication fails.'),
  );

  //pinsever GPG logging fields

  $form['pinserver_logging'] = array(
  '#type' => 'fieldset',
  '#title' => t('Harvard Pinserver Logging'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );

  $form['pinserver_logging']['pinserver_error_log'] = array(
  '#type' => 'textfield',
  '#title' => t('Text file to use for logging GPG stderror output'),
  '#required' => FALSE,
  '#default_value' => variable_get('pinserver_error_log',''),
  '#description' => t('Optionally specify full filename and path from server\'s root directory (not the website\'s root directory). The file should always be below the root directory, and it is recommended only for development sites. Leave blank to disable. Include the first / to indicate the root directory of the webserver.'),
  );

  return system_settings_form($form);
}