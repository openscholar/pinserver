<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function pinserver_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer pinserver
  $permissions['administer pinserver'] = array(
    'name' => 'administer pinserver',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
