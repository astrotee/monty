#include "monty.h"
#include <stdarg.h>
#include <stdlib.h>


/**
* map_instructions - initialise the array of instructions
* @instructions: pointer to the array of instructions
* Return: Nothing
*/
void map_instructions(instruction_t instructions[ISIZE])
{
	instructions[0].opcode = "push";
	instructions[0].f = &push;
	instructions[1].opcode = "pall";
	instructions[1].f = &pall;
	instructions[2].opcode = "pint";
	instructions[2].f = &pint;
	instructions[3].opcode = "pop";
	instructions[3].f = &pop;
	instructions[4].opcode = "swap";
	instructions[4].f = &swap;
	instructions[5].opcode = "add";
	instructions[5].f = &add;
	instructions[6].opcode = "nop";
	instructions[6].f = &nop;
	instructions[7].opcode = "sub";
	instructions[7].f = &sub;
	instructions[8].opcode = "div";
	instructions[8].f = &_div;
	instructions[9].opcode = "mul";
	instructions[9].f = &mul;
	instructions[10].opcode = "mod";
	instructions[10].f = &mod;
	instructions[11].opcode = "pchar";
	instructions[11].f = &pchar;
	instructions[12].opcode = "pstr";
	instructions[12].f = &pstr;
	instructions[13].opcode = "rotl";
	instructions[13].f = &rotl;
	instructions[14].opcode = "rotr";
	instructions[14].f = &rotr;
	instructions[15].opcode = "stack";
	instructions[15].f = &op_stack;
	instructions[16].opcode = "queue";
	instructions[16].f = &op_queue;
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
