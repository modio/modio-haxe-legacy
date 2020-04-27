import ModioWrapper;

class Ex05_AutomaticDownloads 
{
  static function main()
  {
    var wait = function()
    {
      while (true)
      {
        // The download queue help us tracking the download progress
        var download_queue:Array<Dynamic> = ModioWrapper.getModDownloadQueue();
        if(download_queue.length > 0)
        {
          trace("=== Download queue ===");
          trace("Queue size: " + download_queue.length);
          for(i in 0...download_queue.length)
          {
            trace("[" + i + "]: " + download_queue[i].mod.name);
            if(download_queue[i].current_progress > 0)
            {
              var progress = download_queue[i].current_progress / download_queue[i].total_size;
              progress = Math.round( progress * 100 * Math.pow(10, 2) ) / Math.pow(10, 2);
              trace("Progress: " + download_queue[i].current_progress + "/" + download_queue[i].total_size + "(" + progress + "%)");
            }
          }
        }
        ModioWrapper.process();
        Sys.sleep(.017);
      }
    }

    ModioWrapper.init(ModioWrapper.ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", "");

    // Everytime a mod finished intalling the download listener function will be called
    trace("Listening to mod installs...");
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
      trace("You are not logged in.");
      trace("Installed mods will be automatically updated.");
      trace("Please log in to install new mods automatically by subscribing to to them.");
    }else
    {
      trace("You are logged in.");
      trace("Installed mods will be automatically updated.");
      trace("You can install new mods by subscribing to them.");
    }

    trace("Press ctrl-c to exit.");
    
    wait();
  }
}