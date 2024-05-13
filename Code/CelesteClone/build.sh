#!/bin/bash

libs="-luser32 -lgdi32 -lopengl32"
warnings="-Wno-writable-strings -Wno-format-security -Wno-deprecated-declarations"
includes="-Ivendor"

clang++ $includes -g src/Main.cpp -obin/game.exe $libs $warnings