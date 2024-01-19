#include "monty.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

global_object gb;


/**
* main - the main function
* @argc: the argument count
* @argv: the arguments values
* Return: the exit status code
*/
int main(int argc, char **argv)
{
	int i;
	char *opcode;
	unsigned int lineno = 0;
	size_t len = 0;
	ssize_t nread;
	stack_t *stack = NULL;
	instruction_t instructions[ISIZE];

	map_instructions(instructions);
	if (argc != 2)
		_exiterr(&stack, "USAGE: monty file\n");
	gb.file = fopen(argv[1], "r");
	if (gb.file == NULL)
		_exiterr(&stack, "Error: Can't open file %s\n", argv[1]);
	while ((nread = getline(&gb.line, &len, gb.file)) != -1)
	{
		lineno++;
		opcode = strtok(gb.line, " \n");
		if (opcode == NULL || opcode[0] == '#')
			continue;
		gb.oparg = strtok(NULL, " \n");
		for (i = 0; i < ISIZE; i++)
			if (strcmp(instructions[i].opcode, opcode) == 0)
			{
				instructions[i].f(&stack, lineno);
				break;
			}
		if (i == ISIZE)
			_exiterr(&stack, "L%u: unknown instruction %s\n", lineno, opcode);
	}
	clean(&stack);
	return (EXIT_SUCCESS);
}
