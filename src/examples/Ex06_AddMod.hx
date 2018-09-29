import ModioWrapper;

class Ex06_AddMod
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

    // The upload listener will be called once the modfile has finished uploading
    ModioWrapper.setUploadListener(function(response_code:Int, mod_id:Int)
    {
      trace("Response code: " + response_code);
      if(response_code >= 200 && response_code < 300)
      {
        trace("A modfile was added to the mod " + mod_id);
      }else
      {
        trace("Error uploading modfile to mod " + mod_id);
      }
      finish();
    });

    if(!is_logged_in)
    {
      trace("You are not logged in. Please authenticate before adding a mod.");
      finish();
    }else
    {
      // The Mod Creator helps setting up the fields before creating a Mod
      var mod_creator:ModCreator = new ModCreator();
      // The mod's name, logo path and summary are required fields that must be set in order to create a mod profile
      mod_creator.setName("Haxe mod test");
      mod_creator.setLogoPath("ModExample/logo.png");
      mod_creator.setSummary("This is a mod example created from the Haxe wrapper.");
      // You can set other optional fields as well
      mod_creator.setVisible(ModioWrapper.PUBLIC);
      mod_creator.setMaturityOption(ModioWrapper.MATURITY_DRUGS | ModioWrapper.MATURITY_VIOLENCE);
      mod_creator.setDescription("This is a description from the Haxe wrapper. This shuld be at least 100 characters long. So it must be a long description.");
      mod_creator.setHomepage("http://haxewrapper.mod.com");
      mod_creator.setMetadata("testing metadata from haxe wrapper");
      mod_creator.addTag("Easy");
      // The name id is optional but must be unique so please be aware, if the name_id already exists the API will return 422 as response code
      //mod_creator.setNameid("unique-mod-id");

      // Now we can create the new mod. Remember, this mod wont have a Modfile right away, you should be adding one after the mod was created successfully
      ModioWrapper.addMod(mod_creator, function(response:Dynamic, mod:Dynamic)
      {
        trace("Response code: " + response.code);
        if (response.code == 201)
        {
          trace("Mod created successfully");

          // The Modfile Creator helps us setting up the modfile fields and the mod directory that will be zipped and uploaded
          var modfile_creator:ModfileCreator = new ModfileCreator();
          // The only required field to create a modfile is the directory path
          modfile_creator.setPath("ModExample/modfile/");
          // Additionally you can set the following optional fields
          modfile_creator.setVersion("v0.1.2");
          modfile_creator.setChangelog("This is changelog was set on the Haxe wrapper.");
          modfile_creator.setActive(true);
          // The filehash helps your users to validate the file arrived correctly to the mod.io API
          //modfile_creator.setFilehash("2d4a0e2d7273db6b0a94b0740a88ad0d");

          ModioWrapper.addModfile(mod.id, modfile_creator);
        }else
        {
          trace("Error creating mod");
          finish();
        }
      });
    }
    wait();
  }
}