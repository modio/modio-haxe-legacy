#!/bin/bash
g++ -L./lib/linux64 ./src/modioWrapper.cpp -shared -o ./bin/modioWrapper.ndll -I./include -lmodio -fPIC -Wl,-rpath .
haxe -cp src -main Main -cpp bin -D HXCPP_M64
LD_LIBRARY_PATH=./bin/ ./bin/Main
