@echo off
mkdir bin
cl /D_USRDLL /D_WINDLL ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp lib/windows32/modio.lib /I include /link /DLL /OUT:bin/modioWrapperWindows_x86.ndll
haxe -cp src -main Main -cpp bin -D windows
copy lib\windows32\modio.dll bin
cd bin
Main.exe
pause