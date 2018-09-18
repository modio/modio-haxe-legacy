#!/bin/bash
mkdir bin
MODIO_SDK_PATH="mod.io-sdk-v0.9.0"
MODIO_LINKER_PATH="$MODIO_SDK_PATH/lib/linux/x64"
MODIO_LIBRARY_PATH="$MODIO_LINKER_PATH/libmodio.so"
MODIO_INCLUDE_PATH="$MODIO_SDK_PATH/include"
cp $MODIO_LIBRARY_PATH bin/
g++ -L./$MODIO_LINKER_PATH ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp -shared -o ./bin/modioWrapperLinux_x64.ndll -I./include -I./$MODIO_INCLUDE_PATH -lmodio -fPIC -Wl,-rpath . -std=c++11
haxe -cp src/examples -main Ex01_Authentication -cpp bin -D linux
haxe -cp src/examples -main Ex02_BrowseMods -cpp bin -D linux
haxe -cp src/examples -main Ex03_SubscribeToMod -cpp bin -D linux
haxe -cp src/examples -main Ex04_UnsubscribeFromMod -cpp bin -D linux
haxe -cp src/examples -main Ex05_AutomaticDownloads -cpp bin -D linux
haxe -cp src/examples -main Ex06_AddMod -cpp bin -D linux
haxe -cp src/examples -main Ex07_EditMod -cpp bin -D linux

# Run an individual example by typing the following
# LD_LIBRARY_PATH=./bin ./bin/Ex01_Authentication