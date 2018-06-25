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
  public static var isLoggedIn:Void->Bool = cpp.Lib.load(ndll_name,"modioWrapperIsLoggedIn",0);
  public static var logout:Void->Bool = cpp.Lib.load(ndll_name,"modioWrapperLogout",0);
  public static var emailRequest:String->(Int->Void)->Void = cpp.Lib.load(ndll_name,"modioWrapperEmailRequest",2);
  public static var emailExchange:String->(Int->Void)->Void = cpp.Lib.load(ndll_name,"modioWrapperEmailExchange",2);
  public static var getMods:Int->Int->Int->(Array<Dynamic>->Int->Void)->Int = cpp.Lib.load(ndll_name,"modioWrapperGetMods",4);
  public static var addMod:ModCreator->(Int->Void)->Int = cpp.Lib.load(ndll_name,"modioWrapperAddMod", 2);
}