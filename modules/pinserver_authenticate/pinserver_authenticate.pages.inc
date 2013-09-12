<?php

/**
 * Page callback
 *
 * Allows for login via PIN to be the default action of /user
 */
function pinserver_authenticate_default_user_login() {
  global $user;
  module_load_include('pages.inc', 'user');

  if ($user->uid && isset($_GET['destination']) && $_GET['destination'] != 'user'){
    //Redirect to destination
    drupal_goto();
  }
  elseif ($user->uid) {
    menu_set_active_item('user/' . $user->uid);
    return menu_execute_active_handler(NULL, FALSE);
  }
  else {
    return drupal_get_form('user_login');
  }
}

/**
 * Routing function
 *
 * See flowchart in pinserver_authenticate.module.com
 */
function pinserver_authenticate_pin_user_login() {
  // Auth error
  if ($errors = pinserver_get_errors()) {
    foreach ($errors as $e) {
      watchdog(WATCHDOG_ERROR, t('Pinserver authentication error: @error', array('@error' => $e)));
      error_log(t('Pinserver authentication error: @error', array('@error' => $e)));
    }
  }
  // System confic error
  if ($error = pinserver_check_system_settings()) {
    watchdog(WATCHDOG_ERROR, t('Pinserver connection error: @error', array('@error' => $error)));
    error_log(t('Pinserver connection error: @error', array('@error' => $error)));
    drupal_set_message('Unable to connect to pinserver. Contact your site administrator.', 'error');
    drupal_goto('user');
  }
  // Not logged in
  elseif (!pinserver_get_user_huid()) {
    $url = 'user/pin';
    $options = array(
      'absolute' => TRUE,
    );
    if (isset($_GET['destination'])) {
      $options['query']['destination'] = $_GET['destination'];
      unset($_GET['destination']);
    }
    $url = url($url, $options);
    $pin_options = array(
      'redirect' => $url,
    );
    if ($GLOBALS['base_url'] != variable_get('purl_base_domain', $GLOBALS['base_url'])) {
      $url = url('pinserver/auth', array('query' => array('redirect' => $url), 'absolute' => TRUE));
      $pin_options = array(
        'redirect' => $url,
        'tk_forward' => 1
      );
    }
    pinserver_redirect($pin_options);
  }
  // Given PIN has a user linked to it
  elseif ($uid = pinserver_authenticate_get_uid_from_huid(pinserver_get_user_huid())) {
    $GLOBALS['user'] = user_load($uid);
    user_login_finalize();
    drupal_goto('user');
  }
  // Given PIN has no user linked to it
  else {
    // Users needs to create a full account to continue further
    if (isset($_GET['destination'])) {
      $args = array('destination' => $_GET['destination']);
      unset($_GET['destination']);
    }
    else {
      $args = array('destination' => 'user');
    }
    drupal_goto('user/pin/create', array('query' => $args));
  }
}

/**
 * Page for PIN users that have no Drupal account linked for this pin
 * Gives them 3 choices of what to do when
 */
function pinserver_authenticate_user_create() {
  $output = array(
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'pinserver_authenticate').'/css/pinserver_authenticate.create.css'
      )
    )
  );

  $query = array(
    'destination' => 'user'
  );
  if (isset($_GET['destination'])) {
    $query['destination'] = $_GET['destination'];
  }

  $output['notice'] = array(
    '#markup' => t('Sorry, but we don\'t have an OpenScholar account associated with your Harvard University ID (HUID).<br />'),
    '#weight' => -2,
  );

  $output['login'] = array(
    '#prefix' => '<span id="pin-login" class="pin-button">',
    '#markup' => l('Login with your existing account to link it with your HUID.', 'user/login', array('query' => $query)),
    '#suffix' => '</span>'
  );

  $menu_item = menu_get_item('site/register');
  if ($menu_item['access']) {
    $output['new_site'] = array(
      '#prefix' => '<span id="pin-register" class="pin-button">',
      '#markup' => l('Create a OpenScholar site and account for this HUID', 'site/register'),
      '#suffix' => '</span>'
    );
  }
  else {
    $output['new_site'] = array(
      '#prefix' => '<span id="pin-no-user">',
      '#markup' => t('You may not create a new account. A site manager must create an account for you before you can log in.'),
      '#suffix' => '</span>',
      '#weight' => -1
    );
  }

  $output['nevermind'] = array(
    '#prefix' => '<span id="pin-nvm" class="pin-button">',
    '#markup' => l('Do nothing and return to where you were.', 'user/pin/cancel', array('query' => $query)),
    '#suffix' => '</span>'
  );

  return $output;
}

/**
 * Clears the PIN session so this PIN isn't accidentally linked with an account later
 * Then sends them back to where they were, or user, if they were nowhere.
 */
function pinserver_authenticate_cancel() {
  pinserver_remove_session();
  drupal_goto('user');
}