.PHONY: configure build test

configure:
	cmake . -B build
build:
	cmake --build build
run:
	cmake --build build
	./build/main
