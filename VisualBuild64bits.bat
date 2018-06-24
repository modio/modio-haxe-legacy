@echo off
mkdir bin
cl /D_USRDLL /D_WINDLL ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp lib/windows64/modio.lib /I include /link /DLL /OUT:bin/modioWrapper.ndll
haxe -cp src -main Main -cpp bin -D HXCPP_M64
copy lib\windows64\modio.dll bin
cd bin
Main.exe