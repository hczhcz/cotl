#!/bin/sh

# build and run

if ! type gprof > /dev/null
then
    sudo apt-get install gprof
fi

# if ! type gprof2dot > /dev/null
# then
#     sudo apt-get install python graphviz
#     # TODO add gprof2dot
# fi

./build_cc.sh gcc -g -pg -O1 "$@"

echo "======== ./output/cotl ========"
cd output
./cotl
cd ..

echo "======== gprof ./output/cotl ========"
gprof ./output/cotl ./output/gmon.out > ./output/prof.txt
# gprof2dot ./output/prof.txt > ./output/prof.dot
# dot -Tpng -o ./output/prof.png
