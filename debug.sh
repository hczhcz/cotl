#!/bin/sh

# call lldb or gdb

db="lldb"
if ! type "$db" > /dev/null
then
    db="lldb-3.6"
fi
if ! type "$db" > /dev/null
then
    db="lldb-3.5"
fi
if ! type "$db" > /dev/null
then
    db="lldb-3.4"
fi
if ! type "$db" > /dev/null
then
    db="lldb-3.3"
fi
if ! type "$db" > /dev/null
then
    db="lldb-3.2"
fi
if ! type "$db" > /dev/null
then
    db="gdb"
fi
if ! type "$db" > /dev/null
then
    sudo apt-get install gdb
fi

"$db" "./output/cotl"
