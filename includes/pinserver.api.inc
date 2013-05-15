<?php

/**
 * API function - Checks if user can access registration form by checking $_SESSION values
 * The $_SESSION values are only set when a user succesfully
 * @return unknown
 */
function pinserver_check_status(){
  global $user;
  
  //allow admin to access the form
  if ($user->uid == '1'){
    //return true; // for testing purposes
  }
  if (isset($_SESSION['pinserver']['reg_time']) && isset($_SESSION['pinserver']['huid'])){
    return true;
  }
  return false;
}

/**
 * API function - Return all session values (set after successful pinserver login)
 */
function pinserver_get_session(){
  //returns array with pinserver session values if not empty
  if (!empty($_SESSION['pinserver'])){
    foreach ($_SESSION['pinserver'] as $key => $val){
      $session_values['key'] = $val;
    }
    return $session_values;
  }
  else{
    return FALSE;
  }
}

/**
 * API function - Returns huid (set after successful pinserver login)
 */
function pinserver_get_session_huid(){
  //returns array with pinserver session values
  if ($_SESSION['pinserver']['huid']){
    return $_SESSION['pinserver']['huid'];
  }
  else{
    return FALSE;
  }
}

/**
 * API function - Remove session values set after successful pinserver login
 */
function pinserver_remove_session(){
  //removing session values when new site is created
  if (isset($_SESSION['pinserver'])){
    unset ($_SESSION['pinserver']);
  }
}