main: main.c
	gcc -std=c99 -o main main.c -ggdb -pedantic -Wall -Wextra -fanalyzer
run:
	./main
