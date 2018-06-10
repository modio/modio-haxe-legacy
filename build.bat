@echo off
mkdir bin
mingw32-g++.exe -L. ./src/modioGlue.cpp -shared -o ./bin/modio.ndll -I./include -lmodio
haxe -cp src -main Main -cpp bin -D HXCPP_M64
cd bin
Main.exe