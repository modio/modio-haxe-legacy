@echo off
mkdir bin
REM mingw32-g++.exe -L. ./src/modioGlue.cpp -shared -o ./bin/modio.ndll -I./include -lmodio
cl /LD ./src/modioGlue.cpp modio.lib /I include ./bin/modio.ndll
haxe -cp src -main Main -cpp bin -D HXCPP_M64
cd bin
Main.exe