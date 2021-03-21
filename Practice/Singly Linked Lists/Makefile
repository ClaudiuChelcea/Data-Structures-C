# Chelcea Claudiu

FLAGS=-Wall -Wextra
NAME=exec
TARGETS=main.o functions.o

build: main functions link

main: main.c
	gcc -c main.c $(FLAGS)

functions: functions.c
	gcc -c functions.c $(FLAGS)

link: $(TARGETS)
	gcc -o $(NAME) $(TARGETS) $(FLAGS)
	rm $(TARGETS)

clean:
	rm -rf $(NAME) $(TARGETS)

.PHONY: clean
