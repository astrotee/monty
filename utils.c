#include "monty.h"
#include <stdarg.h>
#include <stdlib.h>


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
* clean - exit with an error message
* @stack: pointer to the stack top
* Return: Nothing
*/
void clean(stack_t **stack)
{
	if (gb.line)
		free(gb.line);
	if (gb.file)
		fclose(gb.file);
	freestack(stack);
}

/**
* _exiterr - exit with an error message
* @stack: pointer to the stack top
* @msg: the error message
* Return: Nothing
*/
void _exiterr(stack_t **stack, char *msg, ...)
{
	va_list args;

	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);
	clean(stack);
	exit(EXIT_FAILURE);
}
