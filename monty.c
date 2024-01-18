#include "monty.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

global_object gb;


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
	int iarg;
	(void)line_number;

	if (gb.oparg == NULL)
		_exiterr(stack, "L%u: usage: push integer\n", line_number);
	iarg = atoi(gb.oparg);
	while (gb.oparg[i])
	{
		if (!isdigit(gb.oparg[i]))
			_exiterr(stack, "L%u: usage: push integer\n", line_number);
		i++;
	}

	new = (stack_t *)malloc(sizeof(stack_t));
	if (new == NULL)
		_exiterr(stack, "Error: malloc failed\n");
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
	char *opcode;
	unsigned int lineno = 0;
	size_t len = 0;
	ssize_t nread;
	stack_t *stack = NULL;
	instruction_t instructions[2];

	instructions[0].opcode = "push";
	instructions[0].f = &push;
	instructions[1].opcode = "pall";
	instructions[1].f = &pall;
	if (argc != 2)
		_exiterr(&stack, "USAGE: monty file\n");
	gb.file = fopen(argv[1], "r");
	if (gb.file == NULL)
		_exiterr(&stack, "Error: Can't open file %s\n", argv[1]);
	while ((nread = getline(&gb.line, &len, gb.file)) != -1)
	{
		lineno++;
		opcode = strtok(gb.line, " \n");
		if (opcode == NULL)
			continue;
		gb.oparg = strtok(NULL, " \n");
		if (strcmp("push", opcode) == 0)
			instructions[0].f(&stack, lineno);
		else if (strcmp("pall", opcode) == 0)
			instructions[1].f(&stack, lineno);
		else
			_exiterr(&stack, "L%u: unknown instruction %s\n", lineno, opcode);
	}
	clean(&stack);
	return (EXIT_SUCCESS);
}
