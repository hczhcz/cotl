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

rm ./output/*

for file in ./source/*.cpp
do
    echo "======== $(basename $file) ========"
    "$cc" -c $ccflags $dflags $flags "$file" -o "./output/$(basename $file .cpp).o"
done

echo "======== linking ========"
# if libgc is already installed, use -lgc
# "$cc" $dflags $flags ./output/*.o ./gc/*.o -o "./output/cotl"
"$cc" $dflags $flags ./output/*.o -lgc -o "./output/cotl"
