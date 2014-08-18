#!/bin/sh

# a simple script to build cotl
# use clang++ -O1 by default

cc="clang++"
if ! type "$cc" > /dev/null
then
    cc="g++"
fi
if ! type "$cc" > /dev/null
then
    sudo apt-get install g++
fi

dflags="-Wall -Wextra"

flags="$@"
if [ "$flags" = "" ]
then
    flags="-std=c++11 -g -O1"
fi

rm ./output/*

for file in ./source/*.cpp
do
    echo "======== $(basename $file) ========"
    "$cc" -c $dflags $flags "$file" -o "./output/$(basename $file .cpp).o"
done

echo "======== linking ========"
# if libgc is already installed, use -lgc
# "$cc" $dflags $flags ./output/*.o ./gc/*.o -o "./output/cotl"
"$cc" $dflags $flags ./output/*.o -lgc -o "./output/cotl"
