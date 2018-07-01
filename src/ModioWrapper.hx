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

class ModEditor
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

class ModfileCreator
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

class ModioWrapper
{
  public static var MODIO_ENVIRONMENT_LIVE = 0;
  public static var MODIO_ENVIRONMENT_TEST = 1;

  public static var MODIO_SORT_BY_ID            = 0;
  public static var MODIO_SORT_BY_RATING        = 1;
  public static var MODIO_SORT_BY_DATE_LIVE     = 2;
  public static var MODIO_SORT_BY_DATE_UPDATED  = 3;

  #if (linux)
    static var ndll_name:String = "modioWrapperLinux_x64";
  #end
  #if (windows)
    static var ndll_name:String = "modioWrapperWindows_x86";
  #end

  public static var init:Int->Int->String->Void = cpp.Lib.load(ndll_name,"modioWrapperInit",3);
  public static var process:Void->Void = cpp.Lib.load(ndll_name,"modioWrapperProcess",0);
  
  public static var emailRequest:String->(Int->Void)->Void = cpp.Lib.load(ndll_name,"modioWrapperEmailRequest",2);
  public static var emailExchange:String->(Int->Void)->Void = cpp.Lib.load(ndll_name,"modioWrapperEmailExchange",2);
  public static var isLoggedIn:Void->Bool = cpp.Lib.load(ndll_name,"modioWrapperIsLoggedIn",0);
  public static var logout:Void->Bool = cpp.Lib.load(ndll_name,"modioWrapperLogout",0);
  public static var getMods:Int->Int->Int->(Array<Dynamic>->Int->Void)->Int = cpp.Lib.load(ndll_name,"modioWrapperGetMods",4);
  public static var subscribeToMod:Int->(Int->Void)->Void = cpp.Lib.load(ndll_name,"modioWrapperSubscribeToMod",2);
  public static var unsubscribeFromMod:Int->(Int->Void)->Void = cpp.Lib.load(ndll_name,"modioWrapperUnsubscribeFromMod",2);
  public static var installMod:Int->Void = cpp.Lib.load(ndll_name,"modioWrapperInstallMod",1);
  public static var uninstallMod:Int->Void = cpp.Lib.load(ndll_name,"modioWrapperUninstallMod",1);
  public static var pauseDownloads:Void->Void = cpp.Lib.load(ndll_name,"modioWrapperPauseDownloads",0);
  public static var resumeDownloads:Void->Void = cpp.Lib.load(ndll_name,"modioWrapperResumeDownloads",0);
  public static var prioritizeDownload:Int->Void = cpp.Lib.load(ndll_name,"modioWrapperPrioritizeDownload",1);
  public static var setDownloadListener:(Int->Int->Void)->Void = cpp.Lib.load(ndll_name,"modioWrapperSetDownloadListener",1);
  public static var getModDownloadQueue:Void->Array<Dynamic> = cpp.Lib.load(ndll_name,"modioWrapperGetModDownloadQueue",0);
  public static var setUploadListener:(Int->Int->Void)->Void = cpp.Lib.load(ndll_name,"modioWrapperSetUploadListener",1);
  public static var getModfileUploadQueue:Void->Array<Dynamic> = cpp.Lib.load(ndll_name,"modioWrapperGetModfileUploadQueue",0);
  public static var getInstalledMods:Void->Array<Dynamic> = cpp.Lib.load(ndll_name,"modioWrapperGetInstalledMods",0);
  public static var getModState:Int->Int = cpp.Lib.load(ndll_name,"modioWrapperGetModState",1);
  public static var addMod:ModCreator->(Int->Void)->Int = cpp.Lib.load(ndll_name,"modioWrapperAddMod", 2);
  public static var editMod:Int->ModEditor->(Int->Void)->Int = cpp.Lib.load(ndll_name,"modioWrapperEditMod", 3);
  public static var addModfile:Int->ModfileCreator->(Int->Void)->Int = cpp.Lib.load(ndll_name,"modioWrapperAddModfile", 2);
  public static var getAuthenticatedUser:(Int->Dynamic->Void)->Int = cpp.Lib.load(ndll_name,"modioWrapperGetAuthenticatedUser", 1);
}