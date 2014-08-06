#!/bin/sh

# a simple script to build cotl
# use clang++ -O2 by default

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

"$cc" $dflags $flags ./output/*.o -o "./output/cotl"
