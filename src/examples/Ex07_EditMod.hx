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

    ModioWrapper.init(ModioWrapper.ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");
    var is_logged_in = ModioWrapper.isLoggedIn();

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
      mod_editor.setVisible(ModioWrapper.PUBLIC);
      mod_editor.setMaturityOption(ModioWrapper.MATURITY_DRUGS | ModioWrapper.MATURITY_VIOLENCE);
      //mod_editor.setNameid("unique-mod-id");
      mod_editor.setDescription("This is an edited description from the Haxe wrapper. This shuld be at least 100 characters long. So it must be a long description.");
      mod_editor.setHomepage("http://edited.mod.com");
      mod_editor.setMetadata("editing metadata from haxe wrapper");

      ModioWrapper.editMod(mod_id, mod_editor, function(response:Dynamic, mod:Dynamic)
      {
        trace("Response code: " + response.code);
        if (response.code == 200)
        {
          trace("Mod edited successfully");
        }else
        {
          trace("Error editing mod");
        }
        finish();
      });
    }
    wait();
  }
}