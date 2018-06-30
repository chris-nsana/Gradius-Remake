#!/bin/bash
mkdir build
currentPath=$(pwd)
goalPath=/build
runPath=/bin
buildDir="$currentPath$goalPath"
binDir="$currentPath$runPath"
cd $buildDir
cmake $currentPath
make install
cd $binDir
./Gradius


