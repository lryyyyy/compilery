all: build unit_test

build:
	./run.sh

unit_test:
	@ ./unit_test

clean:
	@ rm -rf ./build ./unit_test

.PHONY: all build unit_test clean
