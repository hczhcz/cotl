#!/bin/sh

# https://github.com/ivmai/bdwgc

cd gc

autoreconf -vif &&
automake --add-missing &&
./configure &&
make
make check

cd ..
