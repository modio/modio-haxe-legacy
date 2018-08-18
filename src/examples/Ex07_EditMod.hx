import ModioWrapper;

class Ex07_EditMod
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

    if(!is_logged_in)
    {
      trace("You are not logged in. Please authenticate before editing a mod.");
      finish();
    }else
    {
      trace("Enter the mod id: ");
      var mod_id:Int = Std.parseInt(Sys.stdin().readLine());

      // The Mod Editor helps setting up the fields that will be updated
      var mod_editor:ModEditor = new ModEditor();
      mod_editor.setName("Haxe mod edit");
      mod_creator.setVisible(ModioWrapper.MODIO_PUBLIC);
      mod_creator.setMaturityOption(ModioWrapper.MODIO_MATURITY_DRUGS | ModioWrapper.MODIO_MATURITY_VIOLENCE);
      //mod_creator.setNameid("unique-mod-id");
      mod_creator.setDescription("This is a description from the Haxe wrapper. This shuld be at least 100 characters long. So it must be a long description.");
      mod_creator.setHomepage("http://haxewrapper.mod.com");
      mod_creator.setMetadata("testing metadata from haxe wrapper");
      mod_creator.addTag("Easy");

      ModioWrapper.editMod(mod_id, mod_editor, function(response_code:Int, mod:Dynamic)
      {
        trace("Response code: " + response_code);
        if (response_code == 200)
        {
          trace("Mod edited successfully");
        }else
        {
          trace("Error editing mod");
          trace(response_code);
          finish();
        }
      });
    }
    wait();
  }
}