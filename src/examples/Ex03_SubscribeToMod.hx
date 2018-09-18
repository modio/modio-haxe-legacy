import ModioWrapper;

class Ex03_SubscribeToMod
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

    // Users can subscribe to mods to download and keep them updated
    // This can be achieved by calling "ModioWrapper.process()" continiously, downloads will occur automatically on the background
    trace("Enter the mod id: ");
    var mod_id:Int = Std.parseInt(Sys.stdin().readLine());

    ModioWrapper.subscribeToMod(mod_id, function(response:Dynamic)
    {
      trace("Response code: " + response.code);
      if(response.code == 201)
      {
        trace("You are now subscribed to the mod!");
      }
      else
      {
        trace("Error subscribing to mod.");
      }
      finish();
    });
    
    wait();
  }
}