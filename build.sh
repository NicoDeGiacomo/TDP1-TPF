#!/bin/sh
rm -r build || exit
mkdir build || exit
cd build || exit
cmake .. || exit
make || exit
./TESTS