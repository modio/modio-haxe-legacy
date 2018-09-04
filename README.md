This project is a [Haxe wrapper](https://apps.mod.io/haxe-wrapper) of the [mod.io SDK](https://apps.mod.io/sdk) available on [Github](https://sdk.mod.io). It's currently compatible with Windows 32 bits, Linux 64 bits, and Mac OS. The wrapper still does not cover all the functionality the SDK provides yet but it's ready to offer fundamental mods support for your games. The mod.io's [getting started guide](https://apps.mod.io/guides/getting-started) is a good place to start if you are completely new to [mod.io](https://mod.io/) and it's [API](https://docs.mod.io/#getting-started).

# Getting started

Instead of building the wrapper yourself, you can download precompiled binares on the [releases tab](https://github.com/Turupawn/modioHaxe/releases/). Once you have done that, follow this steps:
1. Place the corresponing `.dll`, `.so` or `.dylib` next to your executable. They are located in the `Libs/` directory.
2. Again, place the corresponding `.ndll` next to your executable. They are located in the `NDLLs/` directory.
3. Import the `ModioWrapper.hx` file it in your Haxe project.

Once this is done, you can call all the static functions under the `ModioWrapper` class. See the [Main.hx](https://github.com/Turupawn/modioHaxe/blob/master/src/Main.hx) example for details and the [wiki](https://github.com/Turupawn/modioHaxe/wiki) for the list of implemented functions so far.

## OpenFL

In case you are using OpenFL, take a look at the OpenFL [installation tutorial](https://github.com/Turupawn/modioOpenFLExample#openfl-integration) and [examples](https://github.com/Turupawn/modioOpenFLExample/tree/master/Source).

# Building the NDLL

The NDLL acts as a "glue code" between C and Haxe, you write your functions on C and then you can call them on Haxe by using Haxe's [C Foreign Functions Interface](http://old.haxe.org/doc/cpp/ffi). You build the NDLL just like any other shared library on your C++ compiler. Use the corresponing command to build it.

Before starting, make sure you have installed [Haxe](https://haxe.org/download/). Once you finished installed Haxe, install `haxelib` by typing `haxe install hxcpp` on your terminal.

## Visual Studio on Windows

Note: This should work on *Visual Studio 15 2017* and newer versions. You will need to additionally install the *Visual Studio C++ Redistributable*.

```bash
cl /D_USRDLL /D_WINDLL ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp lib/windows32/modio.lib /I include /link /DLL /OUT:./modioWrapperWindows_x86.ndll
```

This will generate the `modioWrapperWindows_x86.ndll`.

## G++ on Linux

```bash
g++ -L./lib/linux64 ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp -shared -o ./modioWrapperLinux_x64.ndll -I./include -lmodio -fPIC -Wl,-rpath .
```

This will generate the `modioWrapperLinux_x64.ndll`.

## Clang on Mac OS

```bash
clang++ -shared -L./lib/macos -lmodio ./src/modioWrapper.cpp ./src/modioWrapperCallbacks.cpp ./src/modioWrapperObjects.cpp -o ./modioWrapperMacOS.ndll -I./include -std=c++11
```

This will generate the `modioWrapperMacOS.ndll`.

# Shell Scripts

`LinuxBuild64bits.sh`, `MacOSBuild.sh` and `VisualBuild32bits.bat` have been added to this repository to automate the building and testing process. Feel free to use and adapt them to your own setup.
