#!/bin/sh
rm -r build
mkdir build || exit
cd build || exit
cmake -D_PRODUCTION_MODE=1 .. || exit
make || exit
valgrind  --leak-check=full --track-fds=yes ./TESTS