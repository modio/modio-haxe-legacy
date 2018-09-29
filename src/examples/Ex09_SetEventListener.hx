import ModioWrapper;

class Ex09_SetEventListener {
	static function main() {
		var wait = function() {
			while (true) {
				ModioWrapper.process();
				Sys.sleep(.017);
			}
		}

		ModioWrapper.init(ModioWrapper.ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

		// Everytime a mod finished intalling the download listener function will be called
		trace("Listening to mod events...");
		ModioWrapper.setEventListener(function(response:Dynamic, events:Array<Dynamic>) {
			if (response.code == 200 || response.code == 206) {
				trace("Event found!");

				for (event in events) {

          var event_type = "";

					if(event.event_type == ModioWrapper.EVENT_UNDEFINED)
							event_type = "undefined";
					else if(event.event_type == ModioWrapper.EVENT_UNDEFINED)
							event_type = "undefined";
					else if(event.event_type == ModioWrapper.EVENT_MODFILE_CHANGED)
							event_type = "modfile changed";
					else if(event.event_type == ModioWrapper.EVENT_MOD_AVAILABLE)
							event_type = "mod available";
					else if(event.event_type == ModioWrapper.EVENT_MOD_UNAVAILABLE)
							event_type = "mod unavailable";
					else if(event.event_type == ModioWrapper.EVENT_MOD_EDITED)
							event_type = "mod edited";
					else if(event.event_type == ModioWrapper.EVENT_USER_TEAM_JOIN)
							event_type = "user team join";
					else if(event.event_type == ModioWrapper.EVENT_USER_TEAM_LEAVE)
							event_type = "user team leave";
					else if(event.event_type == ModioWrapper.EVENT_USER_SUBSCRIBE)
							event_type = "user subscribe";
					else if(event.event_type == ModioWrapper.EVENT_USER_UNSUBSCRIBE)
							event_type = "user unsubscribe";

					trace("Id:" + event.id);
					trace("Mod id:" + event.mod_id);
					trace("User id:" + event.user_id);
					trace("Event type:" + event_type);
					trace("Date added:" + event.date_added);
				}
			} else {
				trace("Error listening to events.");
			}
		});

		var is_logged_in = ModioWrapper.isLoggedIn();
		if (!is_logged_in) {
			trace("You are not logged in.");
			trace("Installed mods will be automatically updated.");
			trace("Please log in to install new mods automatically by subscribing to to them.");
		} else {
			trace("You are logged in.");
			trace("Installed mods will be automatically updated.");
			trace("You can install new mods by subscribing to them.");
		}

		trace("Press ctrl-c to exit.");

		wait();
	}
}
