default: bake

bake:
	mkdir -p build 
	cd build; cmake ..; make -j3

runc:
	cd bin; ./client

runs:
	cd bin; ./server

docs:
	doxygen

all: build docs runc

clean:
	rm -r doc
	rm -r build
