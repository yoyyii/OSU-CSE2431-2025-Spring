# compile statement
gcc_opt = -std=c99 -pedantic -Wimplicit-function-declaration -Wreturn-type -Wformat -g -c

# all targets currently defined in this file
all: lab1.zip lab1

# zip file
lab1.zip: Makefile helloworld.c
	zip lab1.zip Makefile helloworld.c

# binary converter executable
lab1: helloworld.o
	gcc helloworld.o -o lab1

helloworld.o: helloworld.c
	gcc $(gcc_opt) helloworld.c

# clean
clean:
	rm -rf *.o lab1 lab1.zip

# verify everything is zip correctly
test:
	./verify



