CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99
DEBUG=-g -ggdb -O0 -march=native

build: Test

Test: Test.o Queue.o LinkedList.o ListGraph.o Stack.o
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

ListGraph.o: ListGraph.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

LinkedList.o: LinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

Queue.o: Queue.c
	$(CC) $(CFLAGS) $(DEBUG)  $^ -c -o $@

Stack.o: Stack.c
	$(CC) $(CFLAGS) $(DEBUG)  $^ -c -o $@

Test.o:  Test.c
	$(CC) $(CFLAGS) $(DEBUG)  $^ -c -o $@

run: Test
	.$<

clean:
	rm -f *.o Test
