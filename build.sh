#!/bin/bash
g++ -L. ./src/modioGlue.cpp -shared -o ./bin/modioGlue.ndll -I./include -lmodio -fPIC -Wl,-rpath .
haxe -cp src -main Main -cpp bin -D HXCPP_M64
LD_LIBRARY_PATH=./bin/ ./bin/Main