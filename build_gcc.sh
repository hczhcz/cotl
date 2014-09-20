#!/bin/sh

# build cotl
# use clang++ -O1 by default

cc="g++"

if ! type "$cc" > /dev/null
then
    sudo apt-get install g++
fi

ccflags="-c"
pchflags="-x c++-header"
dflags="-std=c++11 -Wall -Wextra"
flags="$@"
lflags="-lgc"

if [ "$flags" = "" ]
then
    flags="-g -O1"
fi

if ! grep "^#define _COTL_USE_GLOBAL_GC" cotl_config > /dev/null
then
    lflags="./gc/*.o -ldl -lpthread"
fi
if ! grep "^#define _COTL_USE_GC" cotl_config > /dev/null
then
    lflags=""
fi

rm ./output/*

echo "======== precompiling ========"
"$cc" $pchflags $dflags $flags "cotl" -o "./cotl.pch"

for file in ./source/*.cpp
do
    echo "======== $(basename $file) ========"
    "$cc" $ccflags $dflags $flags -include "cotl" "$file" -o "./output/$(basename $file .cpp).o" || exit
    nm -C -l -p "./output/$(basename $file .cpp).o" |
        grep "cotl" |
        sed -e "s:^[0-9A-Fa-f]* *::g" |
        sed -e "s:$(pwd).*/::g" > "./output/$(basename $file .cpp).nm"
done

echo "======== linking ========"
"$cc" $dflags $flags $lflags ./output/*.o -o "./output/cotl"
nm -C -l -p "./output/cotl" |
    grep "cotl" |
    sed -e "s:^[0-9A-Fa-f]* *::g" |
    sed -e "s:$(pwd).*/::g" > "./output/cotl.nm"
readelf -a "./output/cotl" > "./output/cotl.readelf"
