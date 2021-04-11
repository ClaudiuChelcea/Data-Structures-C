# Chelcea Claudiu Marian

# Define setup
FLAGS=-Wall -Wextra -g
CC=clang
OBJECTS=graphs.o linkedlist.o main.o
TARGETS=graphs linkedlist main linker

# COMPILE
build: $(TARGETS)

graphs:	graphs.c
	$(CC) -c $(FLAGS) graphs.c

linkedlist: linkedlist.c
	$(CC) -c $(FLAGS) linkedlist.c

main: main.c
	$(CC) -c $(FLAGS) main.c

linker: $(TARGETS)
	$(CC) -o exec $(FLAGS) $(OBJECTS)

# Clean
clean:
	rm -rf *.o
	rm exec

.PHONY: clean
