#!/bin/bash
mkdir bin
cp mod.io-sdk-v0.8.0/lib/linux/x64/libmodio.so bin/
g++ -L./mod.io-sdk-v0.8.0/lib/linux/x64 ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp -shared -o ./bin/modioWrapperLinux_x64.ndll -I./include -I./mod.io-sdk-v0.8.0/include -lmodio -fPIC -Wl,-rpath .
haxe -cp src/examples -main Ex01_Authentication -cpp bin -D linux
haxe -cp src/examples -main Ex02_BrowseMods -cpp bin -D linux
haxe -cp src/examples -main Ex03_SubscribeToMod -cpp bin -D linux
haxe -cp src/examples -main Ex04_UnsubscribeFromMod -cpp bin -D linux
haxe -cp src/examples -main Ex05_AutomaticDownloads -cpp bin -D linux
haxe -cp src/examples -main Ex06_AddMod -cpp bin -D linux
haxe -cp src/examples -main Ex07_EditMod -cpp bin -D linux

# Run an individual example by typing the following
# LD_LIBRARY_PATH=./bin ./bin/Ex01_Authentication