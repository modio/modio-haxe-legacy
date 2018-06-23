class Mod
{
    public var x:Int;
    public function new()
    {
    }
}

class ModCreator
{
    public var logo_path:String;
    public var name:String;
    public var summary:String;
    public function new()
    {
        logo_path = "";
        name = "";
        summary = "";
    }
}

class Main 
{
    static var modioWrapperInit:Int->Int->String->Void = cpp.Lib.load("modioWrapper","modioWrapperInit",3);
    static var modioWrapperProcess:Void->Void = cpp.Lib.load("modioWrapper","modioWrapperProcess",0);
    static var modioWrapperIsLoggedIn:Void->Bool = cpp.Lib.load("modioWrapper","modioWrapperIsLoggedIn",0);
    static var modioWrapperLogout:Void->Bool = cpp.Lib.load("modioWrapper","modioWrapperLogout",0);
    static var modioWrapperEmailRequest:String->(Int->Void)->Void = cpp.Lib.load("modioWrapper","modioWrapperEmailRequest",2);
    static var modioWrapperEmailExchange:String->(Int->Void)->Void = cpp.Lib.load("modioWrapper","modioWrapperEmailExchange",2);
    static var modioWrapperGetMods:Int->Int->Int->(Array<Dynamic>->Int->Void)->Int = cpp.Lib.load("modioWrapper","modioWrapperGetMods",4);
    //static var modioWrapperTestPointer:Dynamic->Int = cpp.Lib.load("modioWrapper","modioWrapperTestPointer",1);
    static var finished = false;

    static function onEmailExchange(resonse_code:Int)
    {
        if (resonse_code == 200)
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

    static function onEmailRequest(resonse_code:Int)
    {
        if (resonse_code == 200)
        {
            trace("Email request successful");
            
            trace("Please enter the 5 digit security code:");
            var security_code = Sys.stdin().readLine();
            modioWrapperEmailExchange(security_code, onEmailExchange);
        }
        else
        {
            trace("Error sending code");
            finished = true;
        }
    }

    static function main()
    {
        modioWrapperInit(1, 7, "e91c01b8882f4affeddd56c96111977b");

        /*
        var is_logged_in = modioWrapperIsLoggedIn();
        if(!is_logged_in)
        {
            modioWrapperEmailRequest("ahmed.hn.43@gmail.com", onEmailRequest);
        }else
        {
            trace("You are already logged in. Do you want to logout? (y/n)");
            var option = Sys.stdin().readLine();
            if(option=="y")
            {
                modioWrapperLogout();
            }
            finished = true;
        }
        */

        var x:Mod = new Mod();

//        trace(modioWrapperTestPointer(x));
/*
        modioWrapperGetMods(0, 4, 2, function (mods:Array<Dynamic>, resonse_code:Int)
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

        while (!finished)
        {
            modioWrapperProcess();
        }
    }
}