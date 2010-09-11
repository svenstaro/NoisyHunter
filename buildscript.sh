#!/bin/bash

if [ ! -d "./build" ]; then
	mkdir -p "./build" || exit 1
fi

cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j3 && cd ..
