#!/bin/sh

# build and run

# less error message
set -e

./build.sh "$@"
echo "======== time ./output/cotl ========"
time ./output/cotl
