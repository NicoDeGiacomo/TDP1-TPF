#!/bin/sh
rm -r build
mkdir build
cd build || exit
cmake .. || exit
make || exit