import ModioWrapper;

class Ex02_BrowseMods
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

    var mods_per_page = 4;
    var page = 0;
    ModioWrapper.getMods(ModioWrapper.MODIO_SORT_BY_RATING, mods_per_page, page * mods_per_page, function(mods:Array<Dynamic>, response_code:Int)
    {
      trace("Response code: " + response_code);
      if(response_code == 200)
      {
        for (i in 0...mods_per_page)
        {
          trace("Id: " + mods[i].id);
          trace("Name: " + mods[i].name);
          trace("Description: " + mods[i].description + "\n");
        }
        finish();
      }
    });
    
    wait();
  }
}