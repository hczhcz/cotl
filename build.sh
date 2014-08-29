#!/bin/sh

# a simple script to build cotl
# use clang++ -O1 by default

cc="clang++"
# ccflags="-flto -emit-llvm"
ccflags=""
if ! type "$cc" > /dev/null
then
    cc="g++"
    ccflags=""
fi
if ! type "$cc" > /dev/null
then
    sudo apt-get install g++
fi

dflags="-std=c++11 -Wall -Wextra"

flags="$@"
if [ "$flags" = "" ]
then
    flags="-g -O1"
fi

lflags="-lgc"
if ! grep "^#define _COTL_USE_GLOBAL_GC" cotl_config > /dev/null
then
    lflags="./gc/*.o"
fi
if ! grep "^#define _COTL_USE_GC" cotl_config > /dev/null
then
    lflags=""
fi

rm ./output/*

for file in ./source/*.cpp
do
    echo "======== $(basename $file) ========"
    "$cc" -c $ccflags $dflags $flags "$file" -o "./output/$(basename $file .cpp).o"
done

echo "======== linking ========"
"$cc" $dflags $flags $lflags ./output/*.o -o "./output/cotl"
