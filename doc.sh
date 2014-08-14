#!/bin/sh

echo "======== doxygen ========"
doxygen ./Doxyfile &&
firefox ./doc/html/index.html
