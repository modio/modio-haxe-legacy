@echo off
mkdir bin
copy "mod.io-sdk-v0.10.0\bin\nmake\x86\modio.dll" bin
cl /D_USRDLL /D_WINDLL ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp mod.io-sdk-v0.10.0/lib/nmake/x86/modio.lib /I include /I mod.io-sdk-v0.10.0/include /link /DLL /OUT:bin/modioWrapperWindows_x86.ndll
haxe -cp src -main Main -cpp bin -D windows
cd bin
Main.exe
pause