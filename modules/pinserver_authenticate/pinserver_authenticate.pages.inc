<?php

/**
 * Redirects to pinserver if they are not logged in
 * Prompts to
 */
function pinserver_authenticate_pin_user_login() {
  if ($errors = pinserver_get_errors()) {
    foreach ($errors as $e) {
      watchdog(WATCHDOG_ERROR, t('Pinserver authentication error: @error', array('@error' => $e)));
      error_log(t('Pinserver authentication error: @error', array('@error' => $e)));
    }
  }
  if ($error = pinserver_check_system_settings()) {
    watchdog(WATCHDOG_ERROR, t('Pinserver connection error: @error', array('@error' => $error)));
    error_log(t('Pinserver connection error: @error', array('@error' => $error)));
    drupal_set_message('Unable to connect to pinserver. Contact your site administrator.', 'error');
    drupal_goto('user');
  }
  elseif (!pinserver_authenticate_user() && !pinserver_get_user_huid()) {
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
    $args['__authen_application'] = variable_get('pinserver_app_name');
    $redirect_url = url(variable_get('pinserver_pin_url'),array('query' => $args));
    $output = array(
      '#markup' => '<a href="'.$redirect_url.'">Click to login.</a>'
    );
    return $output;
  }
  elseif ($uid = pinserver_authenticate_get_uid_from_huid(pinserver_get_user_huid())) {
    $GLOBALS['user'] = user_load($uid);
    user_login_finalize();
    drupal_goto('user');
  }
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
 * Allows user to fill in the rest of their user account
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

  $output['nevermind'] = array(
    '#prefix' => '<span id="pin-nvm" class="pin-button">',
    '#markup' => l('Do nothing and return to where you were.', $_GET['destination']),
    '#suffix' => '</span>'
  );

  return $output;
}

function pinserver_authenticate_user_create_form_submit($form, &$form_state) {
  module_load_include('inc', 'os', 'includes/user');
  $values = $form_state['values'];

  $user_options = array(
    'name' => $values['name'],
    'pass' => $values['password'],
    'mail' => $values['mail'],
    'status' => 1,
    'field_first_name' => $values['first_name'],
    'field_last_name' => $values['last_name'],
  );
  $user = os_user_create($user_options);
  pinserver_authenticate_set_user_huid($user->uid, pinserver_get_user_huid());

  $GLOBALS['user'] = $user;
  user_login_finalize();
}
