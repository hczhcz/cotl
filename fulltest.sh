#!/bin/sh

# build, lint, doc, memtest

./build.sh "$@"
./check.sh
./doc.sh
echo "======== valgrind ./output/cotl ========"
valgrind ./output/cotl
