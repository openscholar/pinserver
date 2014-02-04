This is a Drupal 7 module for allowing HUID login.  It is an
adaptation of the Drupal 6 module pinserver, from IQSS, 
and pinserver\_osc by Reinhard Engels.  Note that although this module
works, it is not currently in use on a production site.  The Drupal 6
two-module predecessor to this one is working on the Office for
Scholarly Communication's sites, however.

This module implements PIN 1 and 2, but not 3.

A D7 version of pinserver is at
https://github.com/openscholar/pinserver.  A later version of this
module may break out the additional functionality in order to take
advantage of the current IQSS module.

Installation
------------

    cd sites/all/modules/
    git clone git@git.huit.harvard.edu:pin-server-module-for-drupal-7/pinserver_plus.git
    drush en pinserver_plus

Or enable the module in the UI.

Configuration
-------------

Go to http://yoursite/#overlay=admin/settings/pinserver_plus.  You will need an
application name and target, GPG, and LDAP login credentials.  Instructions are 
linked at https://github.com/openscholar/pinserver/blob/7.x-3.x/README.md. 

The salt is added to the HUID when creating a hash.  In the case of
the OSC, this had to match the salt used in DASH, so Drupal users
could be mapped to DASH users.  Your application may vary.

TODO
----

- Put search string in configuration
- Add facility for putting HUID users in a role?
- Take some or all config out of UI?
