# Harvard PIN

A drupal 7 module

## About

Provides developer API for the
[Harvard University PIN system](http://www.pin.harvard.edu/). Similar to
single-sign-on (SSO), Harvard PIN allows anyone with a Harvard ID to access
exclusive Harvard-only websites or services, based on the public-private-key
based PGP, OpenPGP or GPG standard. This module handles low-level details of
Harvard PIN for Drupal integration.

The module was developed for the [OpenScholar](http://openscholar.harvard.edu)
Drupal profile (distribution). However, the module does not depend on
OpenScholar or any non-core module, and can be used in any Drupal 7 site.

Some possible applications for this module are:

* Protected content; restrict certain nodes to only allow Harvard PIN access
* Harvard PIN user authentication; only allow users to log in with Harvard PIN.

## Install

In order to get a working PIN application on a Drupal site, you will need to:

1. [Install the module](http://drupal.org/documentation/install/modules-themes)
2. [Register as a PIN2 customer](http://reference.pin.harvard.edu/dev-registration)
3. [Download and install GPG](http://www.gnupg.org/download/index.en.html)
4. [Create a GPG key on your server](http://www.dewinter.com/gnupg_howto/english/GPGMiniHowto-3.html#ss3.1)
5. [Import the Harvard PIN public key](http://www.dewinter.com/gnupg_howto/english/GPGMiniHowto-3.html#ss3.3)
6. Send your public GPG key to directory_services@harvard.edu
7. Configure your GPG and Harvard PIN application info at /admin/settings/pinserver

Note: This module currently only implements Harvard PIN API version 1 and
version 2. There is currently no support in this module for Oracle Access
Manager (Harvard PIN API version 3).

For more information about developing with PIN, see the
[Harvard PIN Customer Guide](http://reference.pin.harvard.edu/dev-overview)
or the Harvard PIN2 Developer Resources PDF](http://reference.pin.harvard.edu/sites/reference.pin.harvard.edu/files/PIN2%20Developer%20Resources.pdf)

## Contribute

* Write help and docs in our [wiki](https://github.com/openscholar/pinserver/wiki)
* Submit a bug or ask for support at our [issue queue](https://github.com/openscholar/pinserver/issues)
* Contribute with bug fixes and new features by sending us pull requests  

## Credits

Joe Weiner [@jjweiner](https://github.com/jjweiner), Richard Brandon [@rbran100](https://github.com)
, Shane Dupree [@shanedupree](https://github.com/shanedupree), 
Oren Robinson [@baisong](https://github.com/baisong) Seth Gregory, Blaise Freeman, 
Ferdi Alimadhi [@Ferdi](https://github.com/Ferdi) for their contribution with code and/or ideas.

Special thanks to [IQSS](http://iq.harvard.edu) and [HWP](http://hwp.harvard.edu) for supporting our work.
