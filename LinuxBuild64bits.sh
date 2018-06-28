#!/bin/bash
mkdir bin
cp lib/linux64/libmodio.so bin/
g++ -L./lib/linux64 ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp -shared -o ./bin/modioWrapperLinux_x64.ndll -I./include -lmodio -fPIC -Wl,-rpath .
haxe -cp src -main Main -cpp bin -D linux 
LD_LIBRARY_PATH=./bin ./bin/Main
