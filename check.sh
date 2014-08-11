#!/bin/sh

# run cppcheck

echo "======== cppcheck ========"
cppcheck . -i ./gc -f --std=c++11 --enable=warning --enable=style --enable=missingInclude -q
