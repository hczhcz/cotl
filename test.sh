#!/bin/sh

# build and run

./build.sh "$@"
echo "======== time ./output/cotl ========"
time ./output/cotl
