@echo off
mkdir bin
copy "mod.io-sdk-v0.8.0\bin\nmake\x86\modio.dll" bin
cl /D_USRDLL /D_WINDLL ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp mod.io-sdk-v0.8.0/lib/nmake/x86/modio.lib /I include /I mod.io-sdk-v0.8.0/include /link /DLL /OUT:bin/modioWrapperWindows_x86.ndll
haxe -cp src -main Main -cpp bin -D windows
haxe -cp src/examples -main Ex01_Authentication -cpp bin -D windows
haxe -cp src/examples -main Ex02_BrowseMods -cpp bin -D windows
haxe -cp src/examples -main Ex03_SubscribeToMod -cpp bin -D windows
haxe -cp src/examples -main Ex04_UnsubscribeFromMod -cpp bin -D windows
haxe -cp src/examples -main Ex05_AutomaticDownloads -cpp bin -D windows
haxe -cp src/examples -main Ex06_AddMod -cpp bin -D windows
haxe -cp src/examples -main Ex07_EditMod -cpp bin -D windows