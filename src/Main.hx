import ModioWrapper;

class Main 
{
    static function onEmailExchange(response_code:Int)
    {
        if (response_code == 200)
        {
            trace("Code exchanged! You are now logged in.");
            trace("Listening to events...");
        }
        else
        {
            trace("Error exchanging code");
            Sys.exit(0);
        }
        return;
    }

    static function onEmailRequest(response_code:Int)
    {
        if (response_code == 200)
        {
            trace("Email request successful");
            
            trace("Please enter the 5 digit security code:");
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
        ModioWrapper.init(ModioWrapper.MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

        ModioWrapper.setDownloadListener(function(response_code:Int, mod_id:Int)
        {
            if(response_code == 200 || response_code == 206)
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
            ModioWrapper.emailRequest("ahmed.hn.43@gmail.com", onEmailRequest);
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
            var download_queue:Array<Dynamic>;
            download_queue = ModioWrapper.getModDownloadQueue();
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
}