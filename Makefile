default: bake

bake:
	mkdir -p build 
	cd build; cmake ..; make -j3

runc:
	cd bin; ./client

runs:
	cd bin; ./server

runpongs:
	cd bin; ./pong_server

runpongc:
	cd bin; ./pong_client

edits:
	cd bin; ./editor_server

editc:
	cd bin; ./editor

docs:
	doxygen

all: build docs runc

clean:
	rm -r build
	rm -r doc
