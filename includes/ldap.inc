<?php

/**
 * @file
 * LDAP functions and settings for pinserver module.
 */

// The Harvard LDAP port number.
define('PINSERVER_LDAP_PORT', 636);

// Appended to "uid=$username," to generate $bind_rdn for ldap_connect().
define('PINSERVER_LDAP_BASE_RDN', 'o=Harvard University Core,dc=huid,dc=harvard,dc=edu');

// Passed as $base_dn parameter on ldap_search().
define('PINSERVER_LDAP_BASE_DN', 'ou=people,o=Harvard University Core,dc=huid,dc=harvard,dc=edu');

/**
 * Gets name and email from ldap for given HUID.
 *
 * @param int $huid
 *   A given user's Harvard HUID.
 *
 * @return array $info
 *   An indexed array containing:
 *   - success: TRUE only if there were no errors connecting/binding/querying
 *   the LDAP server.
 *   - errors: An array containing any (string) error messages encountered.
 *   - entries: An indexed array with keys equal to LDAP attribute names,
 *   and values as arrays containing any value(s) found from the search.
 */
function pinserver_ldap_attributes_from_huid($huid) {
  $info = array(
    'success' => FALSE,
  );

  // Prepares LDAP connect and bind settings.
  $hostname = variable_get('pinserver_ldap_hostname', '');
  $uid = variable_get('pinserver_ldap_uid', '');
  $bind_password = variable_get('pinserver_ldap_bind_password', '');
  $base = PINSERVER_LDAP_BASE_RDN;
  $bind_rdn = "uid={$uid},{$base}";
  ldap_set_option(NULL, LDAP_OPT_DEBUG_LEVEL, 7);

  // Attempts to connect to host LDAP server.
  $link_identifier = ldap_connect($hostname, PINSERVER_LDAP_PORT);
  if (!$link_identifier) {
    $info['errors'][] = t('Couldn\'t connect to LDAP host: @hostname.', array('@hostname' => $hostname));
    return $info;
  }

  // Attempts to bind to host LDAP server on resource.
  ldap_set_option($link_identifier, LDAP_OPT_PROTOCOL_VERSION, 3);
  ldap_set_option($link_identifier, LDAP_OPT_REFERRALS, 0);
  $bind = ldap_bind($link_identifier, $bind_rdn, $bind_password);
  dpm(array($_SERVER['HTTP_HOST'], $hostname, PINSERVER_LDAP_PORT, $bind_rdn, $bind_password, $link_identifier, $bind, ldap_error($link_identifier)));
  if (!$bind) {
    $info['errors'][] = t("Couldn't bind to LDAP.");
    return $info;
  }

  // Attempts to search LDAP to find attributes for this HUID.
  $base_dn = PINSERVER_LDAP_BASE_DN;
  $filter = "(&(harvardeduidnumber=" . $huid . "))";
  $result_identifier = ldap_search($link_identifier, $base_dn, $filter);
  if ($result_identifier === FALSE) {
    $info['errors'][] = t('An error occurred while attempting to search LDAP.');
    return $info;
  }

  // Success. Gets entries and returns.
  $info['success'] = TRUE;
  $info['entries'] = ldap_get_entries($link_identifier, $result_identifier);

  return $info;
}
