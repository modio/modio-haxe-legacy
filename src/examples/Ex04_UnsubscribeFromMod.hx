import ModioWrapper;

class Ex04_UnsubscribeFromMod
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

    trace("Enter the mod id: ");
    var mod_id:Int = Std.parseInt(Sys.stdin().readLine());

    ModioWrapper.unsubscribeFromMod(mod_id, function(response:Dynamic)
    {
      trace("Response code: " + response.code);
      if(response.code == 204)
      {
        trace("You are no longer subscribed to the mod");
      }
      else
      {
        trace("Error unsubscribing from mod.");
      }
      finish();
    });
    
    wait();
  }
}