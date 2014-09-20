#!/bin/sh

# see https://github.com/ivmai/bdwgc

if ! test -e ".git"
then
    git init
fi

if ! test -e "gc"
then
    git submodule add git://github.com/ivmai/bdwgc.git gc
fi

cd gc

if ! test -e "libatomic_ops"
then
    git submodule add git://github.com/ivmai/libatomic_ops.git libatomic_ops
fi

# autoreconf -vif &&
# automake --add-missing &&
# ./configure &&
# make
# make check

make gc.a c++ -f Makefile.direct

cd ..
