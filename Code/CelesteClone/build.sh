#!/bin/bash

libs=-luser32
warnings="-Wno-writable-strings -Wno-format-security"

clang -g src/Main.cpp -obin/game.exe $libs $warnings