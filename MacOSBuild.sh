#!/bin/bash
mkdir bin
cp lib/macos/libmodio.dylib bin/
clang++ -shared -L./lib/macos -lmodio ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp -o ./bin/modioWrapperMacOS.ndll -I./include -std=c++11
haxe -cp src -main Main -cpp bin -D macos 
LD_LIBRARY_PATH=./bin ./bin/Main