<?php

/**
 * Returns TRUE user has logged in through pinserver.
 *
 * @param int $timeout
 * - Desired maximum session length, in seconds. Use FALSE for no timeout.
 *
 * @return bool
 */
function pinserver_check_status($timeout = FALSE) {

  // Verifies that the current user has a valid token with reg_time & HUID.
  if ($user = pinserver_get_user_huid()) {
    // Immediately returns TRUE if there is no timeout set.
    if (!$timeout) {
      return TRUE;
    }

    // Otherwise, only returns TRUE if we are before the timeout time.
    $pin_user = pinserver_get_user();
    if (time() < ($pin_user['reg_time'] + $timeout)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Checks if user is Harvard employee based on pinserver variable.
 *
 * @return string or FALSE
 */
function pinserver_is_harvard_employee() {

  if($user = pinserver_get_user() && isset($user['harvard_employee'])){
    return $user['harvard_employee'];
  }

  return FALSE;
}

/**
 * Returns the current pinserver user.
 *
 * @param $user
 * The pin user to set as logged in.
 *
 * @param $use_session
 * Should this pin user be stored in the session.
 */
function pinserver_get_user($user = false, $set_session = false) {
  $pin_user = &drupal_static(__FUNCTION__);

  if($user){
    $pin_user = $user;

    if(isset($_SESSION['pinserver']) || $set_session){
      $_SESSION['pinserver'] = $user;
    }
  }elseif (empty($pin_user) && $_SESSION['pinserver']){
    $pin_user = $_SESSION['pinserver'];
  }

  return $pin_user;
}

/**
 * Returns the huid of the logged-in pinserver user.
 */
function pinserver_get_user_huid() {

  if(($user = pinserver_get_user()) && isset($user['huid'])){
    return $user['huid'];
  }

  return FALSE;
}

/**
 * Remove session values set after successful pinserver login.
 */
function pinserver_remove_session() {
  // Remove session values.
  if (isset($_SESSION['pinserver'])) {
    unset($_SESSION['pinserver']);
  }
}

/**
 * Create a user and set them as logged in using token data.
 */
function pinserver_add_user_from_token($token_data, $use_session = FALSE){

  // Places encrypted harvard uid into session array.
  $pin_user['huid'] = $token_data['user_id'];
  $pin_user['reg_time'] = time();

  if(isset($token_data['department']) && !empty($token_data['department'])) {
    $pin_user['harvard_employee'] = $token_data['department'];
  }

  pinserver_get_user($pin_user, $use_session);
}