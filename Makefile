all: build unit_test

build:
	@cmake -B build
	@cmake --build build
	@cp build/test/unit_test unit_test

unit_test:
	@ ./unit_test

clean:
	@ rm -rf ./build ./unit_test

.PHONY: all build unit_test clean
