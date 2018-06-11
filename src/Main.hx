class Main 
{
    static var modioGlueInit:Int->Int->String->Void = cpp.Lib.load("modioGlue","modioGlueInit",3);
    static var modioGlueProcess:Void->Void = cpp.Lib.load("modioGlue","modioGlueProcess",0);
    static var modioGlueIsLoggedIn:Void->Bool = cpp.Lib.load("modioGlue","modioGlueIsLoggedIn",0);
    static var modioGlueLogout:Void->Bool = cpp.Lib.load("modioGlue","modioGlueLogout",0);
    static var modioGlueEmailRequest:String->(Int->Void)->Void = cpp.Lib.load("modioGlue","modioGlueEmailRequest",2);
    static var modioGlueEmailExchange:String->(Int->Void)->Void = cpp.Lib.load("modioGlue","modioGlueEmailExchange",2);
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
            modioGlueEmailExchange(security_code, onEmailExchange);
        }
        else
        {
            trace("Error sending code");
            finished = true;
        }
    }

    static function main()
    {
        modioGlueInit(1, 7, "e91c01b8882f4affeddd56c96111977b");

        var is_logged_in = modioGlueIsLoggedIn();
        if(!is_logged_in)
        {
            modioGlueEmailRequest("ahmed.hn.43@gmail.com", onEmailRequest);
        }else
        {
            trace("You are already logged in. Do you want to logout? (y/n)");
            var option = Sys.stdin().readLine();
            if(option=="y")
            {
                modioGlueLogout();
            }
            finished = true;
        }

        while (!finished)
        {
            modioGlueProcess();
        }
    }
}