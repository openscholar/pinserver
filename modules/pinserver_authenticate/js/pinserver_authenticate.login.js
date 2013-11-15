(function($) {
  Drupal.behaviors.pinserverAuthenticate = {
    attach: function (ctx) {
      if (localStorage['pin-hide-message']) {
      }
      else {
        $('#columns').addClass('show-msg');
        $('#dont-show').click(function () {
          localStorage['pin-hide-message'] = true;
          $('#columns').removeClass('show-msg');
          $('#pin-message').remove();
        });
      }
    }
  };
})(jQuery);