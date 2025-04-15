# compile statement
gcc_opt = -std=c99 -pedantic -Wimplicit-function-declaration -Wreturn-type -Wformat -g -c

# all targets currently defined in this file
all: lab4.zip lab4 # lab4_ns

# zip file
lab4.zip: Makefile bounded_buffer.h bounded_buffer.c main.c bounded_buffer_ns.h bounded_buffer_ns.c
	zip lab4.zip bounded_buffer.h bounded_buffer.c bounded_buffer_ns.h bounded_buffer_ns.c main.c Makefile

# binary converter executable
# lab4_s: bounded_buffer_s.h bounded_buffer_s.o main.o 
# gcc -pthread bounded_buffer_s.h bounded_buffer_s.o main.o -o lab4_s

lab4: bounded_buffer.h bounded_buffer.o main.o 
	gcc main.c bounded_buffer.c -o lab4 -lpthread -lrt
	
#lab4_ns: bounded_buffer_ns.h bounded_buffer_ns.o main.o 
	# gcc -pthread bounded_buffer_ns.h bounded_buffer_ns.o main.o -o lab4_ns

bounded_buffer.o: bounded_buffer.c bounded_buffer.h
	gcc $(gcc_opt) bounded_buffer.c

# bounded_buffer_ns.o: bounded_buffer_ns.c bounded_buffer_ns.h
	gcc $(gcc_opt) bounded_buffer_ns.c

main.o: main.c bounded_buffer.h # bounded_buffer_ns.h
	gcc $(gcc_opt) main.c

# clean
clean:
	rm -rf *.o lab4 lab4.zip # lab4_ns

# verify everything is zip correctly
test:
	./verify



