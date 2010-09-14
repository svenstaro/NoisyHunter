#!/bin/bash

if [ ! -d "./build" ]; then
	mkdir -p "./build" || exit 1
fi

cd build && cmake .. && make -j3 && cd ..
