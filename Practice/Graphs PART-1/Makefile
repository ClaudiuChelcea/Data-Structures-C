# Chelcea Claudiu Marian

# Define setup
FLAGS=-Wall -Wextra -g
CC=clang
OBJECTS=graphs.o linkedlist.o main.o queue.o stack.o
TARGETS=graphs linkedlist main queue stack linker

# COMPILE
build: $(TARGETS)

graphs:	graphs.c
	$(CC) -c $(FLAGS) graphs.c

linkedlist: linkedlist.c
	$(CC) -c $(FLAGS) linkedlist.c

main: main.c
	$(CC) -c $(FLAGS) main.c

stack: stack.c
	$(CC) -c $(FLAGS) stack.c

queue: queue.c
	$(CC) -c $(FLAGS) queue.c

linker: $(TARGETS)
	$(CC) -o exec $(FLAGS) $(OBJECTS)

# Clean
clean:
	rm -rf *.o
	rm exec

.PHONY: clean
