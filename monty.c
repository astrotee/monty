#include "monty.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

char *argument;

/**
* _exiterr - exit with an error message
* @msg: the error message
* Return: Nothing
*/
void _exiterr(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

/**
* freestack - free the stack nodes
* @stack: pointer to the top of the stack
* Return: Nothing
*/
void freestack(stack_t **stack)
{
	stack_t *cur = *stack, *temp;

	while (cur)
	{
		temp = cur->prev;
		free(cur);
		cur = temp;
	}
	*stack = cur;
}

/**
* push - push an int to the stack
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new;
	int i = 0;
	int iarg = atoi(argument);
	(void)line_number;

	if (argument == NULL)
		_exiterr("L%u: usage: push integer");
	while (argument[i])
	{
		if (!isdigit(argument[i]))
			_exiterr("L%u: usage: push integer");
		i++;
	}

	new = (stack_t *)malloc(sizeof(stack_t));
	new->n = iarg;
	new->next = NULL;
	new->prev = *stack;
	if (*stack)
		(*stack)->next = new;
	*stack = new;
}

/**
* pall - print all values in the stack top to bottom
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *cur = *stack;
	(void)line_number;

	while (cur)
	{
		printf("%d\n", cur->n);
		cur = cur->prev;
	}
}

/**
* main - the main function
* @argc: the argument count
* @argv: the arguments values
* Return: the exit status code
*/
int main(int argc, char **argv)
{
	FILE *file;
	char *line = NULL, *opcode;
	unsigned int lineno = 0;
	int i;
	size_t len = 0;
	ssize_t nread;
	stack_t *stack = NULL;
	instruction_t instructions[2];

	instructions[0].opcode = "push";
	instructions[0].f = &push;
	instructions[1].opcode = "pall";
	instructions[1].f = &pall;
	if (argc != 2)
		_exiterr("USAGE: monty file\n");
	file = fopen(argv[1], "r");
	if (file == NULL)
		_exiterr("Error: Can't open file %s\n");
	while ((nread = getline(&line, &len, file)) != -1)
	{
		lineno++;
		opcode = strtok(line, " \n");
		if (opcode == NULL)
			continue;
		argument = strtok(NULL, " \n");
		for (i = 0; i < 2; i++)
		{
			if (strcmp(instructions[i].opcode, opcode) == 0)
			{
				instructions[i].f(&stack, lineno);
				break;
			}
		}
	}
	free(line);
	fclose(file);
	freestack(&stack);
	return (EXIT_SUCCESS);
}
