#!/bin/sh

# build and run valgrind

./build.sh "$@"
echo "======== valgrind ./output/cotl ========"
valgrind ./output/cotl
