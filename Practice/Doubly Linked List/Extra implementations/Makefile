# Chelcea Claudiu

TARGETS=DoublyExtra.o main.o
FLAGS=-g -Wall -Wextra
CC=clang
NAME=exec

build:DoublyExtra main link

DoublyExtra: DoublyExtra.c
	$(CC) -c $(FLAGS) DoublyExtra.c

main: main.c
	$(CC) -c $(FLAGS) main.c

link: $(TARGETS)
	$(CC) -o $(NAME) $(TARGETS)
	rm -rf $(TARGETS)

clean:
	rm -rf $(TARGETS) $(NAME)

.PHONY: clean


