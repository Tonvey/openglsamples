#!/bin/bash
curPath=$(cd `dirname $BASH_SOURCE`;pwd)
if [ ! -d "$curPath/build" ]
then
    mkdir "$curPath/build"
fi
pushd "$curPath/build"
cmake ..
popd
