all: bin/bf bf.ll test
bin/bf: bf.c
	gcc -Wall -o bin/bf bf.c
bf.ll: bf.c
	clang -S -emit-llvm bf.c
test: bin/bf
	./test.sh

.PHONY: all test
