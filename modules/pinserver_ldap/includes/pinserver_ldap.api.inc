<?php

/**
 * @file
 * API functions for the Pinserver_Plus Plus module.
 * 
 */

/**
 * API function - Checks if user can access registration form by checking $_SESSION values
 * The $_SESSION values are only set when a user succesfully 
 * @return unknown
 */
function pinserver_plus_check_status() {
  global $user;
  
  //allow admin to access the form
  if ($user->uid == '1') {
    //return TRUE; // for testing purposes
  }  
  if (isset($_SESSION['pinserver_plus']['reg_time']) && isset($_SESSION['pinserver_plus']['huid'])) {
    return $reg_time =  ((REQUEST_TIME - (int)$_SESSION['pinserver_plus']['reg_time']) < 120) ? TRUE : FALSE;
  }
  return FALSE;
}

/**
 * API function - Return all session values (set after successful pinserver_plus login)
 */
function pinserver_plus_get_session() {
  //returns array with pinserver_plus session values if not empty  
  if (!empty($_SESSION['pinserver_plus'])) {
    foreach ($_SESSION['pinserver_plus'] as $key => $val) {
      $session_values['key'] = $val;          
    } 
    return $session_values;   
  }
  else {
    return FALSE;
  }
}

/**
 * API function - Returns huid (set after successful pinserver_plus login)
 */
function pinserver_plus_get_session_huid() {
  //returns array with pinserver_plus session values
  if ($_SESSION['pinserver_plus']['huid']) {
    return $_SESSION['pinserver_plus']['huid'];
  }
  else {
    return FALSE;
  }
}

/**
 * API function - Remove session values set after successful pinserver_plus login
 */
function pinserver_plus_remove_session() {
  //removing session values when new site is created
  if (isset($_SESSION['pinserver_plus'])) {
    unset($_SESSION['pinserver_plus']);
  }
}