#!/bin/bash
mkdir bin
cp mod.io-sdk-v0.7.0/lib/linux/x64/libmodio.so bin/
g++ -L./mod.io-sdk-v0.7.0/lib/linux/x64 ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp -shared -o ./bin/modioWrapperLinux_x64.ndll -I./include -I./mod.io-sdk-v0.7.0/include -lmodio -fPIC -Wl,-rpath .
haxe -cp src -main Main -cpp bin -D linux
LD_LIBRARY_PATH=./bin ./bin/Main
