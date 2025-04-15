# compile statement
gcc_opt = -std=c99 -pedantic -Wimplicit-function-declaration -Wreturn-type -Wformat -g -c

# all targets currently defined in this file
all: lab3.zip createThreads parallel1 parallel2 parallel3

# zip file
lab3.zip: Makefile createThreads.c parallel1.c parallel2.c parallel3.c README
	zip lab3.zip Makefile createThreads.c parallel1.c parallel2.c parallel3.c README

# binary converter executable
createThreads: createThreads.o
	gcc -pthread createThreads.o -o createThreads

createThreads.o: createThreads.c
	gcc $(gcc_opt) createThreads.c

parallel1: parallel1.o
	gcc -pthread parallel1.c -o parallel1

parallel1.o: parallel1.c
	gcc $(gcc_opt) parallel1.c

parallel2: parallel2.o
	gcc -pthread parallel2.c -o parallel2

parallel2.o: parallel2.c
	gcc $(gcc_opt) parallel2.c
	
parallel3: parallel3.o
	gcc -pthread parallel3.c -o parallel3

parallel3.o: parallel3.c
	gcc $(gcc_opt) parallel3.c

# clean
clean:
	rm -rf *.o createThreads parallel1 parallel2 parallel3 lab3.zip

# verify everything is zip correctly
test:
	./verify



