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

