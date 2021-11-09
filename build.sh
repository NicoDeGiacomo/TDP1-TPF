#!/bin/sh
rm -r build
mkdir build || exit
cd build || exit
cmake .. || exit
make || exit
./TESTS