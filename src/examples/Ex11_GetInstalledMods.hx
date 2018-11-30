import ModioWrapper;

class Ex11_GetInstalledMods {
	static function main() {
		ModioWrapper.init(ModioWrapper.ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

    var installed_mods:Array<Dynamic> = ModioWrapper.getInstalledMods();

    trace("Installed mods count:" + installed_mods.length);
    for (installed_mod in installed_mods) {
      trace("Mod id:" + installed_mod.mod_id);
      trace("Path:" + installed_mod.path);
    }
	}
}
