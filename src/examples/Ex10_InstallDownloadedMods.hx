import ModioWrapper;

class Ex10_InstallDownloadedMods {
	static function main() {
		var wait = function() {
			while (true) {
				ModioWrapper.process();
				Sys.sleep(.017);
			}
		}

		ModioWrapper.init(ModioWrapper.ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

		trace("Listening to mod events...");
		ModioWrapper.setDownloadListener(function(response_code:Int, mod_id:Int) {
			if (response_code >= 200 && response_code < 300) {
				trace("Mod " + mod_id + " was downloaded.");
				ModioWrapper.installDownloadedMods();
			} else {
				trace("Error listening to events.");
			}
		});

		trace("Press ctrl-c to exit.");

		wait();
	}
}
