@echo off
mkdir bin
cl /D_USRDLL /D_WINDLL ./src/modioGlue.cpp modio.lib /I include /link /DLL /OUT:bin/modioGlue.ndll
haxe -cp src -main Main -cpp bin -D HXCPP_M64
copy modio.dll bin
cd bin
Main.exe