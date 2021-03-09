# Chelcea Claudiu

FLAGS=-Wall -Wextra
NAME=exec
TARGETS=main.o support.o

build: main support link

main: main.c
	gcc -c main.c $(FLAGS)

support: support.c
	gcc -c support.c $(FLAGS)

link: $(TARGETS)
	gcc -o $(NAME) $(TARGETS) $(FLAGS)
	rm $(TARGETS)

clean:
	rf -rf $(NAME)

.PHONY: clean
