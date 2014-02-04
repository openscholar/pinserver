<?php

//@file pinserver_plus.admin.inc

/**
 * pinserver_plus_config()
 *
 * @return array - returns form for pinserver_plus administrative settings
 */
function pinserver_plus_config() {
  global $base_url;

  $form['pinserver_plus'] = array(
  '#type' => 'fieldset',
  '#title' => t('Harvard Pinserver Plus Configuration'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );

  $form['pinserver_plus']['pinserver_plus_pin_url'] = array(
  '#type' => 'textfield',
  '#required' => TRUE,
  '#title' => t('Harvard PIN Server URL'),
  '#default_value' => variable_get('pinserver_plus_pin_url', ''),
  '#description' => t('Enter PIN server URL. For example: https://www.pin1.harvard.edu/pin/authenticate'),
  );

  $form['pinserver_plus']['pinserver_plus_app_name'] = array(
  '#type' => 'textfield',
  '#title' => t('Harvard PIN server application name'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_plus_app_name', ''),
  '#description' => t('Enter the application name given to you by Harvard Directory Services.' ),
  );

  $form['pinserver_plus']['pinserver_plus_target'] = array(
  '#type' => 'textfield',
  '#title' => t('Harvard PIN server target path'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_plus_target', ''),
  '#description' => t('Enter the path given to you by Harvard Directory Services, e.g. "pinserver/auth".' ),
  );

  $form['pinserver_plus']['pinserver_plus_salt'] = array(
  '#type' => 'textfield',
  '#title' => t('Harvard PIN server salt'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_plus_salt', ''),
  '#description' => t('Enter the salt used to encode HUIDs.' ),
  );

  $form['pinserver_plus']['pinserver_plus_ldap_url'] = array(
  '#type' => 'textfield',
  '#title' => t('Harvard LDAP URL'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_plus_ldap_url', ''),
  '#description' => t('Enter the LDAP URL given to you by Harvard Directory Services, something like "ldaps://hu-ldap.harvard.edu".' ),
  );

  $form['pinserver_plus']['pinserver_plus_ldap_user'] = array(
  '#type' => 'textfield',
  '#title' => t('Harvard LDAP user string'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_plus_ldap_user', ''),
  '#description' => t('Enter the LDAP user string given to you by Harvard Directory Services, something like "uid=xyzzy,ou=applications,o=Harvard University Core,dc=huid,dc=harvard,dc=edu".' ),
  );

  $form['pinserver_plus']['pinserver_plus_ldap_password'] = array(
  '#type' => 'textfield',
  '#title' => t('Harvard LDAP password'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_plus_ldap_password', ''),
  '#description' => t('Enter the LDAP password given to you by Harvard Directory Services.' ),
  );

  $form['pinserver_plus']['pinserver_plus_gpg_dir'] = array(
  '#type' => 'textfield',
  '#title' => t('Host server path to public key directory'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_plus_gpg_dir', ''),
  '#description' => t('Enter the absolute path to the GPG directory on your web server where the PIN Server or AuthProxy public key information is stored.' ),
  );

  $form['pinserver_plus']['pinserver_plus_landing_path'] = array(
  '#type' => 'textfield',
  '#title' => t('Landing Path'),
  '#required' => TRUE,
  '#default_value' => variable_get('pinserver_plus_landing_path', ''),
  '#description' => t('Specify the path to redirect the user after all pinserver_plus module processing is complete. Use a relative path that comes after !base_url' . '/', array('!base_url' => $base_url)),
  );

  $form['pinserver_plus']['pinserver_plus_auth_str'] = array(
  '#type' => 'radios',
  '#title' => t('PIN Authentication Server Setup'),
  '#default_value' => variable_get('pinserver_plus_auth_str', ''),
  '#options' => array(
  'Good signature from "Harvard University PIN System' => t('PIN only'),
  'Good signature from "authzproxy"' => t('PIN with AuthProxy'),
  ),
  '#required' => TRUE,
  '#description' => t('The server that is returning the user back to this site after successful PIN login.'),
  );

  $form['pinserver_plus']['pinserver_plus_support_contact'] = array(
  '#type' => 'textfield',
  '#title' => t('E-mail address for technical support'),
  '#required' => FALSE,
  '#default_value' => variable_get('pinserver_plus_support_contact', ''),
  '#description' => t('Optionally specify contact person to be displayed to user if PIN authentication fails.'),
  );

  //pinsever GPG logging fields

  $form['pinserver_plus_logging'] = array(
  '#type' => 'fieldset',
  '#title' => t('Harvard Pinserver Plus Logging'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );

  $form['pinserver_plus_logging']['pinserver_plus_error_log'] = array(
  '#type' => 'textfield',
  '#title' => t('Text file to use for logging GPG stderror output'),
  '#required' => FALSE,
  '#default_value' => variable_get('pinserver_plus_error_log', ''),
  '#description' => t('Optionally specify full filename and path from server\'s root directory (not the website\'s root directory). The file should always be below the root directory, and it is recommended only for development sites. Leave blank to disable. Include the first / to indicate the root directory of the webserver.'),
  );

  return system_settings_form($form);
}