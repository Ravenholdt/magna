#!/bin/bash

if [ ! -f "/build" ]
then
    mkdir -p build
fi

cd build
cmake ..
make
cd ..