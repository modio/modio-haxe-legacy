class ModCreator
{
  // Required fields
  public var logo_path:String;
  public var name:String;
  public var summary:String;
  // Optional fields
  public var visible:Int;
  public var maturity_option:Int;
  public var name_id:String;
  public var description:String;
  public var homepage:String;
  public var metadata:String;
  public var tags:Array<String>;
  public var tags_size:Int;

  public function new()
  {
    logo_path = "";
    name = "";
    summary = "";
    visible = -1;
    maturity_option = -1;
    name_id = "";
    description = "";
    homepage = "";
    metadata = "";
    tags = new Array<String>();
    tags_size = 0;
  }

  // Required fields
  public function setName(name:String)
  {
    this.name = name;
  }
  public function setSummary(summary:String)
  {
    this.summary = summary;
  }
  public function setLogoPath(logo_path:String)
  {
    this.logo_path = logo_path;
  }

  // Optional fields
  public function setVisible(visible:Int)
  {
    this.visible = visible;
  }
  public function setMaturityOption(maturity_option:Int)
  {
    this.maturity_option = maturity_option;
  }
  public function setNameid(name_id:String)
  {
    this.name_id = name_id;
  }
  public function setDescription(description:String)
  {
    this.description = description;
  }
  public function setHomepage(homepage:String)
  {
    this.homepage = homepage;
  }
  public function setMetadata(metadata:String)
  {
    this.metadata = metadata;
  }
  public function addTag(tag:String)
  {
    this.tags.push(tag);
    tags_size++;
  }
}

class ModEditor
{
  public var visible:Int;
  public var maturity_option:Int;
  public var status:Int;
  public var name:String;
  public var name_id:String;
  public var summary:String;
  public var description:String;
  public var homepage:String;
  public var modfile:Int;
  public var metadata:String;

  public function new()
  {
    this.visible = -1;
    this.maturity_option = -1;
    this.status = -1;
    this.name = "";
    this.name_id = "";
    this.summary = "";
    this.description = "";
    this.homepage = "";
    this.modfile = -1;
    this.metadata = "";
  }

  public function setVisible(visible:Int)
  {
    this.visible = visible;
  }
  public function setMaturityOption(maturity_option:Int)
  {
    this.maturity_option = maturity_option;
  }
  public function setStatus(status:Int)
  {
    this.status = status;
  }
  public function setName(name:String)
  {
    this.name = name;
  }
  public function setNameid(name_id:String)
  {
    this.name_id = name_id;
  }
  public function setSummary(summary:String)
  {
    this.summary = summary;
  }
  public function setDescription(description:String)
  {
    this.description = description;
  }
  public function setHomepage(homepage:String)
  {
    this.homepage = homepage;
  }
  public function setModfile(modfile:Int)
  {
    this.modfile = modfile;
  }
  public function setMetadata(metadata:String)
  {
    this.metadata = metadata;
  }
}

class ModfileCreator
{
  // Required field
  public var path:String;
  // Optional fields
  public var version:String;
  public var changelog:String;
  public var active:Bool;
  public var filehash:String;

  public function new()
  {
    path = "";
    version = "";
    changelog = "";
    active = true;
    filehash = "";
  }

  // Required field
  public function setPath(path:String)
  {
    this.path = path;
  }

  // Optional fields
  public function setVersion(version:String)
  {
    this.version = version;
  }
  public function setChangelog(changelog:String)
  {
    this.changelog = changelog;
  }
  public function setActive(active:Bool)
  {
    this.active = active;
  }
  public function setFilehash(filehash:String)
  {
    this.filehash = filehash;
  }
}

class ModioWrapper
{
  // Environment constants
  public static var MODIO_ENVIRONMENT_LIVE = 0;
  public static var MODIO_ENVIRONMENT_TEST = 1;

  // Filter constants
  public static var MODIO_SORT_BY_ID            = 0;
  public static var MODIO_SORT_BY_RATING        = 1;
  public static var MODIO_SORT_BY_DATE_LIVE     = 2;
  public static var MODIO_SORT_BY_DATE_UPDATED  = 3;

  // Mod visibility constants
  public static var MODIO_HIDDEN  = 0;
  public static var MODIO_PUBLIC  = 1;

  // Maturity options
  public static var MODIO_MATURITY_NONE     = 0;
  public static var MODIO_MATURITY_ALCOHOL  = 1;
  public static var MODIO_MATURITY_DRUGS    = 2;
  public static var MODIO_MATURITY_VIOLENCE = 4;
  public static var MODIO_MATURITY_EXPLICIT = 8;

  #if (linux)
    static var ndll_name:String = "modioWrapperLinux_x64";
  #end
  #if (windows)
    static var ndll_name:String = "modioWrapperWindows_x86";
  #end
  #if (macos)
    static var ndll_name:String = "modioWrapperMacOS";
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
  public static var addMod:ModCreator->(Int->Dynamic->Void)->Int = cpp.Lib.load(ndll_name,"modioWrapperAddMod", 2);
  public static var editMod:Int->ModEditor->(Int->Dynamic->Void)->Int = cpp.Lib.load(ndll_name,"modioWrapperEditMod", 3);
  public static var addModfile:Int->ModfileCreator->Int = cpp.Lib.load(ndll_name,"modioWrapperAddModfile", 2);
  public static var getAuthenticatedUser:(Int->Dynamic->Void)->Int = cpp.Lib.load(ndll_name,"modioWrapperGetAuthenticatedUser", 1);
}