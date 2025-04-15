# compile statement
gcc_opt = -std=c99 -pedantic -Wimplicit-function-declaration -Wreturn-type -Wformat -g -c

# all targets currently defined in this file
all: lab2.zip lab2

# zip file
lab2.zip: Makefile shellA.c background.c
	zip lab2.zip Makefile shellA.c background.c

# binary converter executable
lab2: shellA.o
	gcc shellA.o -o lab2

background: background.o
	gcc background.o -o background

shellA.o: shellA.c
	gcc $(gcc_opt) shellA.c

background.o: background.c
	gcc $(gcc_opt) background.c

# clean
clean:
	rm -rf *.o lab2 lab2.zip

# verify everything is zip correctly
test:
	./verify



