main: main.c
	gcc -std=c99 -o $@ $< -ggdb -pedantic -Wall -Wextra -fanalyzer
run: main
	./$<
