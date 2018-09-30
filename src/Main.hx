import ModioWrapper;

class Main 
{
  static function downloadProgressString()
  {
    var installed_mods:Array<Dynamic>;
    installed_mods = ModioWrapper.getInstalledMods();

    var download_queue:Array<Dynamic>;
    download_queue = ModioWrapper.getModDownloadQueue();

    var result:String = "";
    if(installed_mods.length == 1)
    {
      result += installed_mods.length + " mod installed through mod.io. ";
    }else
    {
      result += installed_mods.length + " mods installed through mod.io. ";
    }

    if(download_queue.length > 0)
    {
      result += download_queue.length + " mods downloading. ";
      var current_download = download_queue[0];
      
      if(current_download.current_progress != 0)
      {
        var progress = current_download.current_progress / current_download.total_size;
        progress = Math.round( progress * 100 * Math.pow(10, 2) ) / Math.pow(10, 2);
        result += current_download.current_progress + "/" + current_download.total_size + " (" + progress + "%)";
      }else
      {
        result += "Initializing download, please wait.";
      }
    }else
    {
      result += "Install mods by subscribing to them.";
    }
    return result;
  }

  static function onEmailExchange(response:Dynamic)
  {
    if (response.code == 200)
    {
      trace("Code exchanged! You are now logged in.");
      trace("Listening to events...");
    }
    else
    {
      trace("Error exchanging code");
      Sys.exit(0);
    }
  }

  static function onEmailRequest(response:Dynamic)
  {
    if (response.code == 200)
    {
      trace("Email request successful");
      
      trace("Please enter the 5 digit security code sent to your email:");
      var security_code = Sys.stdin().readLine();
      ModioWrapper.emailExchange(security_code, onEmailExchange);
    }
    else
    {
      trace("Error sending code");
      Sys.exit(0);
    }
  }

  static function main()
  {
    ModioWrapper.init(ModioWrapper.ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

    ModioWrapper.setDownloadListener(function(response:Dynamic, mod_id:Int)
    {
        if(response.code == 200 || response.code == 206)
        {
          trace("Mod installed!");
          trace("Id: " + mod_id);
        }else
        {
          trace("Error installing mod.");
        }
    });

    var is_logged_in = ModioWrapper.isLoggedIn();
    if(!is_logged_in)
    {
      trace("Please type your email:");
      var email = Sys.stdin().readLine();
      ModioWrapper.emailRequest(email, onEmailRequest);
    }else
    {
      trace("You are already logged in. Do you want to logout? (y/n)");
      var option = Sys.stdin().readLine();
      if(option=="y")
      {
        trace("Logging out...");
        ModioWrapper.logout();
        Sys.exit(0);
      }
      trace("Listening to events...");
    }

    while (true)
    {
      trace(downloadProgressString());
      ModioWrapper.process();
      Sys.sleep(.017);
    }
  }
}