
all: monty

monty: *.c
	gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty -g

