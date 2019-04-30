@echo off
mkdir bin
copy "mod.io-sdk-v0.11.1\bin\visualc++\x86\modio.dll" bin
cl /D_USRDLL /D_WINDLL ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp mod.io-sdk-v0.11.1/lib/visualc++/x86/modio.lib /I include /I additional_dependencies /I mod.io-sdk-v0.11.1/include /link /DLL /OUT:bin/modioWrapperWindows_x86.ndll
haxe -cp src -main Main -cpp bin -D windows
cd bin
Main.exe
pause