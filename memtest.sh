#!/bin/sh

# build and run valgrind

# less error message
set -e

./build.sh "$@"
echo "======== valgrind ./output/cotl ========"
valgrind ./output/cotl
