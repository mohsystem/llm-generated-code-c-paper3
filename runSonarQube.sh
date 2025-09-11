#!/bin/bash

# Suppress all warnings
export CFLAGS="-w"
export CXXFLAGS="-w"

# Run the build wrapper and build process, ignoring warnings and errors
clear && build-wrapper-linux-x86-64 --out-dir bw-output cmake --build cmake-build-debug -- -k 0
cd bw-output && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. && cd .. && sonar-scanner
#build-wrapper-linux-x86-64 --out-dir bw-output cmake --build cmake-build-debug -- -k > build.log 2>&1
