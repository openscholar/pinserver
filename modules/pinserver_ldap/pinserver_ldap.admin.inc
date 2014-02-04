<?php

/**
 * @file
 * Includes settings form builder.
 */

/**
 * Settings form builder for LDAP configuration.
 */
function pinserver_ldap_settings_form() {

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

  return system_settings_form($form);
}
