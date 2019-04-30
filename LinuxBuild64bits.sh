#!/bin/bash
mkdir bin
MODIO_SDK_PATH="mod.io-sdk-v0.11.1"
MODIO_LINKER_PATH="$MODIO_SDK_PATH/lib/linux/x64"
MODIO_LIBRARY_PATH="$MODIO_LINKER_PATH/libmodio.so"
MODIO_INCLUDE_PATH="$MODIO_SDK_PATH/include"
cp $MODIO_LIBRARY_PATH bin/
g++ -L./$MODIO_LINKER_PATH ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp -shared -o ./bin/modioWrapperLinux_x64.ndll -I./include -I./$MODIO_INCLUDE_PATH -lmodio -fPIC -Wl,-rpath . -std=c++11
haxe -cp src -main Main -cpp bin -D linux
LD_LIBRARY_PATH=./bin ./bin/Main
