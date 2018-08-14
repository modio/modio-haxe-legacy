import ModioWrapper;

class Ex01_Authentication 
{
  static function main()
  {
    var finished = false;

    var wait = function()
    {
      while (finished == false)
      {
        ModioWrapper.process();
        Sys.sleep(.017);
      }
    }

    var finish = function()
    {
      finished = true;
    }

    ModioWrapper.init(ModioWrapper.MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

    var is_logged_in = ModioWrapper.isLoggedIn();
    if(!is_logged_in)
    {
      trace("Please type your email:");
      var email = Sys.stdin().readLine();
      ModioWrapper.emailRequest(email, function(response_code:Int)
      {
        trace("Response code: " + response_code);
        if (response_code == 200)
        {
          trace("Email request successful");
          
          trace("Please enter the 5 digit security code:");
          var security_code = Sys.stdin().readLine();
          ModioWrapper.emailExchange(security_code, function(response_code:Int)
          {
            if (response_code == 200)
            {
              trace("Code exchanged! You are now logged in.");
            }
            else
            {
              trace("Error exchanging code");
            }
            finish();
          });
        }
        else
        {
          trace("Error sending code");
          finish();
        }
      });
    }else
    {
      trace("You are already logged in. Do you want to logout? (y/n)");
      var option = Sys.stdin().readLine();
      if(option=="y")
      {
        trace("Logging out...");
        ModioWrapper.logout();
        trace("You are now logged out");
        finish();
      }
    }

    wait();
  }
}