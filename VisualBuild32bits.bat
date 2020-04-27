@echo off
mkdir bin
copy "mod.io-sdk-v0.12.12\bin\visualc++\x86\modio.dll" bin
cl /D_USRDLL /D_WINDLL ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp mod.io-sdk-v0.12.12/lib/visualc++/x86/modio.lib /I include /I additional_dependencies /I mod.io-sdk-v0.12.12/include /link /DLL /OUT:bin/modioWrapperWindows_x86.ndll
haxe -cp src -main Main -cpp bin -D windows
cd bin
Main.exe
pause