import ModioWrapper;

class Main 
{
    static var finished = false;

    static function onEmailExchange(response_code:Int)
    {
        if (response_code == 200)
        {
            trace("Code exchanged!");
        }
        else
        {
            trace("Error exchanging code");
        }
        finished = true;
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
            finished = true;
        }
    }

    static function main()
    {
        ModioWrapper.init(ModioWrapper.MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

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
                ModioWrapper.logout();
                finished = true;
            }else
            {
                /*
                trace("Browsing mods");
                var limit = 4;
                var offset = 8;
                ModioWrapper.getMods(ModioWrapper.MODIO_SORT_BY_RATING, limit, offset, function (mods:Array<Dynamic>, resonse_code:Int)
                {
                    if (resonse_code == 200)
                    {
                        trace("Mods retreived successfully");
                        for(i in 0...mods.length)
                        {
                            trace("Id: " + mods[i].id);
                            trace("Name: " + mods[i].name);
                            trace("Description: " + mods[i].description);
                        }
                    }else
                    {
                        trace("Error retreiving mods");
                    }

                    finished = true;
                });
                */

                ///*
                trace("Adding mod");
                var mod_creator = new ModCreator();
                mod_creator.name = "haxe upload test";
                mod_creator.summary = "This was added through the haxe wrapper. This was added through the haxe wrapper. This was added through the haxe wrapper. This was added through the haxe wrapper.";
                mod_creator.logo_path = "../ModExample/logo.png";
                ModioWrapper.addMod(mod_creator, function(response_code:Int)
                {
                    if(response_code == 201)
                    {
                        trace("Mod added");
                    }else
                    {
                        trace(response_code);
                        trace("Error adding mods");
                    }
                    finished = true;
                });
                //*/
            }
        }

        while (!finished)
        {
            ModioWrapper.process();
        }
    }
}