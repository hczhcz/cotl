#!/bin/sh

# run cppcheck

cppcheck ./source ./include -f --std=c++11 --enable=warning --enable=style --enable=missingInclude -q
