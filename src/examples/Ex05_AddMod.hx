import ModioWrapper;

class Ex05_AddMod
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
    trace(is_logged_in);

    ModioWrapper.setUploadListener(function(response_code:Int, mod_id:Int)
    {
      trace("Response code: " + response_code);
      trace("Mod id: " + mod_id);
      finish();
    });

    if(!is_logged_in)
    {
      trace("You are not logged in. Please authenticate before adding a mod.");
      finish();
    }else
    {
      var mod_creator:ModCreator = new ModCreator();
      mod_creator.setName("Haxe mod test");
      mod_creator.setLogoPath("ModExample/logo.png");
      mod_creator.setSummary("This is a mod example created from the Haxe wrapper.");
      ModioWrapper.addMod(mod_creator, function(response_code:Int, mod:Dynamic)
      {
        trace("Response code: " + response_code);
        if (response_code == 201)
        {
          trace("Mod created successfully");

          var modfile_creator:ModfileCreator = new ModfileCreator();
          modfile_creator.setPath("ModExample/modfile/");
          ModioWrapper.addModfile(mod.id, modfile_creator);
        }else
        {
          trace("Error creating mod");
          trace(response_code);
          finish();
        }
      });
    }
    wait();
  }
}