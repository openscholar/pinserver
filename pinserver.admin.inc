<?php

//@file pinserver.admin.inc

/**
 * pinserver_config()
 *
 * @return array - returns form for pinserver administrative settings
 */
function pinserver_config() {
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
    '#default_value' => variable_get('pinserver_pin_url', 'https://www.pin1.harvard.edu/pin/authenticate'),
    '#description' => t('Enter Pin server URL. For example: https://www.pin1.harvard.edu/pin/authenticate'),
  );

  $form['pinserver']['pinserver_app_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Harvard PIN server application name'),
    '#required' => TRUE,
    '#default_value' => variable_get('pinserver_app_name'),
    '#description' => t('Enter the application name given to you by Harvard Directory Services.' ),
  );

  $form['pinserver']['pinserver_gpg_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Host server path to public key directory'),
    '#required' => TRUE,
    '#default_value' => variable_get('pinserver_gpg_dir', DRUPAL_ROOT . '/.gnupg'),
    '#description' => t('Enter the absolute path to the GPG directory on your web server where the PIN Server or AuthProxy public key information is stored.' ),
  );

  $form['pinserver']['pinserver_gpg_bin'] = array(
    '#type' => 'textfield',
    '#title' => t('Host server path to GPG binary'),
    '#required' => TRUE,
    '#default_value' => variable_get('pinserver_gpg_bin', '/usr/bin/gpg'),
    '#description' => t('Enter the absolute path to the GPG executable binary on the server.'),
  );

  $form['pinserver']['pinserver_landing_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Landing Path'),
    '#required' => TRUE,
    '#default_value' => variable_get('pinserver_landing_path', '/site/register'),
    '#description' => t('Specify the path to redirect the user after all pinserver module processing is complete. Use a relative path that comes after "!base_url".', array('!base_url' =>$base_url)),
  );

  $form['pinserver']['pinserver_azp_passphrase'] = array(
    '#type' => 'textfield',
    '#title' => t('AuthZProxy passphrase file'),
    '#required' => FALSE,
    '#default_value' => variable_get('pinserver_azp_passphrase', variable_get('pinserver_gpg_dir', DRUPAL_ROOT . '/.gnupg') . '/azp_passphrase'),
    '#description' => t('Enter the absolute path to the AuthZProxy passphrase file, if your are expecting AuthZProxy tokens.'),
  );

  $form['pinserver']['pinserver_auth_str'] = array(
    '#type' => 'radios',
    '#title' => t('PIN Authentication Server Setup'),
    '#default_value' => variable_get('pinserver_auth_str', 'Good signature from "Harvard University PIN System'),
    '#options' => array(
      'Good signature from "Harvard University PIN System' => t('PIN only'),
      'Good signature from "authzproxy"' => t('PIN with AuthProxy'),
    ),
    '#required' => TRUE,
    '#description' => t('The server that is returning the user back to this site after successful PIN login.'),
  );

  $form['pinserver']['pinserver_hash_huid'] = array(
    '#type' => 'radios',
    '#title' => t('Hash HUIDs for added security'),
    '#default_value' => variable_get('pinserver_hash_huid', '0'),
    '#options' => array(
      '0' => t('HUID is not hashed'),
      '1' => t('HUID is hashed'),
    ),
    '#required' => TRUE,
    '#description' => t('This will store the HUIDs in the OpenScholar database as an MD5 hash instead of plaintext, so they are kept more secure.'),
  );

  $form['pinserver']['pinserver_ip_validation'] = array(
    '#type' => 'radios',
    '#title' => t('IP Validation'),
    '#default_value' => variable_get('pinserver_ip_validation', '1'),
    '#options' => array(
      '0' => t('Don\'t validate IP addresses'),
      '1' => t('Validate IP addresses'),
    ),
    '#required' => TRUE,
    '#description' => t('Verify that $_SERVER[\'REMOTE_ADDR\'] matches the IP passed to us from the PIN server.'),
  );

  $form['pinserver']['pinserver_support_contact'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address for techincal support'),
    '#required' => FALSE,
    '#default_value' => variable_get('pinserver_support_contact'),
    '#description' => t('Optionally specify contact person to be displayed to user if PIN authentication fails.'),
  );


  //pinsever GPG logging fields

  $form['pinserver_logging'] = array(
    '#type' => 'fieldset',
    '#title' => t('Harvard Pinserver Logging'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['pinserver_logging']['pinserver_error_logging_enabled'] = array(
    '#type' => 'radios',
    '#title' => t('Pinserver Error Logging'),
    '#default_value' => variable_get('pinserver_error_logging_enabled', '0'),
    '#options' => array(
      '0' => t('Disabled'),
      '1' => t('Enabled'),
    ),
    '#required' => TRUE,
    '#description' => t('Log GPG output to the file specified below.'),
  );

  $form['pinserver_logging']['pinserver_error_log'] = array(
    '#type' => 'textfield',
    '#title' => t('Text file to use for logging GPG stderror output'),
    '#required' => FALSE,
    '#default_value' => variable_get('pinserver_error_log', '/tmp/pinserver_gpgerror.log'),
    '#description' => t('Optionally specify full filename and path from server\'s root directory (not the website\'s root directory). The file should always be below the root directory, and it is recommended only for development sites. Include the first / to indicate the root directory of the webserver.'),
  );

  return system_settings_form($form);
}
