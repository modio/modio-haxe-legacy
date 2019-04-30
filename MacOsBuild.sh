#!/bin/bash
mkdir bin
cp mod.io-sdk-v0.11.1/lib/macos/x64/libmodio.dylib bin/
clang++ -shared -L./mod.io-sdk-v0.11.1/lib/macos/x64 -lmodio ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp -o ./bin/modioWrapperMacOS.ndll -I./include -I./mod.io-sdk-v0.11.1/include -std=c++11
haxe -cp src -main Main -cpp bin -D macos
LD_LIBRARY_PATH=./bin ./bin/Main