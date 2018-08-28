#!/bin/bash
mkdir bin
cp mod.io-sdk-v0.8.0/lib/macos/x64/libmodio.dylib bin/
clang++ -shared -L./mod.io-sdk-v0.8.0/lib/macos/x64 -lmodio ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp -o ./bin/modioWrapperMacOS.ndll -I./include -I./mod.io-sdk-v0.8.0/include -std=c++11
haxe -cp src/examples -main Ex01_Authentication -cpp bin -D macos
haxe -cp src/examples -main Ex02_BrowseMods -cpp bin -D macos
haxe -cp src/examples -main Ex03_SubscribeToMod -cpp bin -D macos
haxe -cp src/examples -main Ex04_UnsubscribeFromMod -cpp bin -D macos
haxe -cp src/examples -main Ex05_AutomaticDownloads -cpp bin -D macos
haxe -cp src/examples -main Ex06_AddMod -cpp bin -D macos
haxe -cp src/examples -main Ex07_EditMod -cpp bin -D macos

# Run an individual example by typing the following
# LD_LIBRARY_PATH=./bin ./bin/Ex01_Authentication
