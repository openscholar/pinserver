(function ($) {

// global PIN object.

PIN = {};
PIN.swapId= "content-area";
PIN.loginFormId="user-login";
PIN.drupalHtml="";

PIN.createCookie = function(name,value,days) {
    if (days) {
	var date = new Date();
	date.setTime(date.getTime()+(days*24*60*60*1000));
	var expires = "; expires="+date.toGMTString();
    } else {
	var expires = "";
    }
    document.cookie = name+"="+value+expires+"; path=/";
};

PIN.drupalLogin = function(){
    $('#' + PIN.swapId).html(PIN.drupalHtml);
};

PIN.gotoPin =function(){
    // app should be set in Drupal
    document.location = "https://www.pin1.harvard.edu/pin/authenticate?__authen_application="+Drupal.settings.app;
};

PIN.chooseLogin = function() {
    // email should be set in Drupal
    //alert("chooseLogin:  " + window.location.hostname);
    var pin_dest =  document.location.href;
    // extract node url from login url
    pin_dest = pin_dest.replace("/user/login?destination=","/").replace("%2F","/");
    //$.cookie("pin_dest",pin_dest, {path: '/'});
    PIN.createCookie("pin_dest",pin_dest,1); // drupal js api.
    if ( $('#'+PIN.swapId).length === 0 ) {
	PIN.swapId = "pinLoginDiv";
	$('#'+PIN.loginFormId).wrap('<div id=\"' + PIN.swapId + '" />');
	//alert("Yeah, dude!");
    }
    //alert("Hi Reinhard 2: " + PIN.swapId + " NOW length: " + $('#'+PIN.swapId).length);
    PIN.drupalHtml=$('#'+PIN.swapId).html();
    //alert("drupalHtml: " + PIN.drupalHtml);
    var html="";
    html += "<div xmlns=\"http:\/\/di.tamu.edu\/DRI\/1.0\/\" style=\"align:center; text-align: center; width:40%; margin:10px; padding:12px; float:left; border:1px solid #CDCDCD; position: relative;\"> ";
    html += "<form method=\"GET\"> ";
    html += "<button type=\"button\" onclick=\"PIN.gotoPin()\">Login with HUID and PIN<\/button> ";
    html += "<\/form> ";
    html += "<div style=\"text-align: left;\"> ";
    html += "<p>Are you a Harvard Affiliate with Harvard University ID (HUID) and PIN?<\/p>";
    html += "<p>Please click the button above to access this site.<\/p>";
    html += "<p>For more information, please see";
    html += "<a href=\"http:\/\/www.pin.harvard.edu\/login-help.shtml\"> ";
    html += "the PIN Login help page<\/a>.<\/p> ";
    html += "<\/div> ";
    html += "<\/div> ";
    html += "<div style=\"align:center; text-align: center; width:40%; margin:10px; padding:12px; float:left; border:1px solid #CDCDCD; position: relative;\"> ";
    html += "<form method=\"GET\" action=\"\"> ";
    html += "<button type=\"button\" onclick=\"PIN.drupalLogin()\">Login with Password<\/button> ";
    html += "<\/form> ";
    html += "<div style=\"text-align: left;\"> ";
    html += "<p>Not a Harvard Affiliate?</p><p>Please <a href=\"mailto:" + Drupal.settings.email + "\">contact us<\/a> to obtain login credentials, then click the button above.</p>";
    html += "<\/p> ";
    html += "<\/div> ";
    html += "<\/div> ";
    $('#'+PIN.swapId).html(html);    	
};

$(document).ready(function() {
	PIN.chooseLogin();
    });
})(jQuery);
