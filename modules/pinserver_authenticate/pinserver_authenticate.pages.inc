<?php

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
    pinserver_redirect(array('redirect' => $url));
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

  $output['notice'] = array(
    '#markup' => t('Sorry, but we don\'t have an OpenScholar account associated with your PIN.<br />')
  );

  $output['login'] = array(
    '#prefix' => '<span id="pin-login" class="pin-button">',
    '#markup' => l('Login with your existing account to link it with your PIN.', 'user/login'),
    '#suffix' => '</span>'
  );

  $output['new_site'] = array(
    '#prefix' => '<span id="pin-register" class="pin-button">',
    '#markup' => l('Create a OpenScholar site and account for this PIN', 'site/register'),
    '#suffix' => '</span>'
  );

  $query = array(
    'destination' => 'user'
  );
  if (isset($_GET['destination'])) {
    $query['destination'] = $_GET['destination'];
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