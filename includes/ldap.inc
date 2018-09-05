<?php

/**
 * @file
 * LDAP functions and settings for pinserver module.
 */

// The Harvard LDAP port number.
define('PINSERVER_LDAP_PORT', 636);

// Appended to "uid=$username," to generate $bind_rdn for ldap_connect().
define('PINSERVER_LDAP_BASE_RDN', 'ou=applications,o=Harvard University Core,dc=huid,dc=harvard,dc=edu');

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
  $info['errors'][] = t('LDAP connect error: @error', array('@error' => ldap_error($link_identifier)));
  // Attempts to bind to host LDAP server on resource.
  ldap_set_option($link_identifier, LDAP_OPT_PROTOCOL_VERSION, 3);
  ldap_set_option($link_identifier, LDAP_OPT_REFERRALS, 0);
  $bind = ldap_bind($link_identifier, $bind_rdn, $bind_password);
  dpm(array($_SERVER['HTTP_HOST'], $hostname, PINSERVER_LDAP_PORT, $bind_rdn, $bind_password, $link_identifier, $bind, ldap_error($link_identifier)));
  if (!$bind) {
    $info['errors'][] = t('LDAP bind failed. Error: @error', array('@error' => ldap_error($link_identifier)));
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

/**
 *
 */

/**
 *
 */
function getLDAPCreds() {
  $creds = array(
    'ldap_server'	=> 'ldaps://hu-ldap.harvard.edu',
    'ldap_pass'	 => variable_get('pinserver_ldap_bind_password',''),
    'ldap_user'	 => 'uid=' . variable_get('pinserver_ldap_uid') . ',ou=applications,o=Harvard University Core,dc=huid,dc=harvard,dc=edu',
    'ldap_trees'	=> array("ou=people", "ou=jobs"),
    'people_dn'	 => 'ou=people,o=Harvard University Core,dc=huid,dc=harvard,dc=edu',
    'jobs_dn'	 => 'ou=jobs,o=Harvard University Core,dc=huid,dc=harvard,dc=edu',
  );

  return $creds;
}

/**
 *
 */
function getLDAPUser($huid) {
  $output = 'Fetching credentials...';
  $ldap_creds = getLDAPCreds();
  dpm($ldap_creds);
  $ldap_server = $ldap_creds['ldap_server'];
  $ldap_user = $ldap_creds['ldap_user'];
  $ldap_pass = $ldap_creds['ldap_pass'];;
  $ldap_trees = $ldap_creds['ldap_trees'];
  $people_dn = $ldap_creds['people_dn'];
  $jobs_dn = $ldap_creds['jobs_dn'];

  $ds=ldap_connect($ldap_server);  // must be a valid LDAP server!

  $user = array();
  if ($ds) {
    if (!ldap_set_option($ds, LDAP_OPT_PROTOCOL_VERSION, 3)) {
      $output .= "Failed to set LDAP Protocol version to 3, TLS not supported. ";
    }
    //	 if (!ldap_start_tls($ds)) {
    //	 error("ldap_start_tls failed " . ldap_err2str(ldap_errno()));
    //	 }

    #get person info
    $r=ldap_bind($ds, $ldap_user, $ldap_pass);
    if (!$r) {
      $output .= 'failure creating LDAP bind: ' . ldap_err2str(ldap_errno());
    }

    $sr=ldap_search($ds, $people_dn, "(harvardEduIDNumber=$huid)");
    if (!$sr) {
      $output .= 'failure executing LDAP search: ' . ldap_err2str(ldap_errno());
    }

    $info = ldap_get_entries($ds, $sr);
    dpm($info, "info");
    $info = $info[0];

    $output .= prettyPrintLDAP($info);

    #get job info
    if (FALSE) {
      $job = $info['harvardeduprimejobdn'][0];
      list($job) = explode(',', $job);
      if ($job) {
        getLDAPJobInfo($job, $ds);
      }
    }
  } else {
    $output .= ldap_err2str(ldap_errno());
  }

  return $output;
}

/**
 *
 */
function getLDAPJobInfo($job, $ds) {
  $jobs_dn = 'ou=jobs,o=Harvard University Core,dc=huid,dc=harvard,dc=edu';

  $sr=ldap_search($ds, $jobs_dn, "($job)");
  $job = ldap_get_entries($ds, $sr);

  $job = $job[0];

  prettyPrintLDAP($job);
}

/**
 *
 */
function prettyPrintLDAP($ldap) {
  $output = '';
  foreach ($ldap as $k => $vs) {
    if (is_array($vs)) {
      $output .= $k . "<br/>";

      $has_val = false;
      foreach ($vs as $vk => $v) {
        if (preg_match('/^\d+$/', $vk) && strlen($v)) {
          $output .= " * " . $v . "<br/>";
          $has_val = true;
        }
      }
      if (!$has_val) {
        $output .= " * (no value)\n";
      }
      $output .= "<br/>";
    }
  }

  return $output;
}
