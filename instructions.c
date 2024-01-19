#include "monty.h"
#include <ctype.h>
#include <stdlib.h>

/**
* swap - swap the top two elements of the stack
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (*stack == NULL || (*stack)->prev == NULL)
		_exiterr(stack, "L%u: can't swap, stack too short\n", line_number);
	temp = (*stack)->n;
	(*stack)->n = (*stack)->prev->n;
	(*stack)->prev->n = temp;
}

/**
* pop - pop the top of the stack
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
		_exiterr(stack, "L%u: can't pop an empty stack\n", line_number);
	temp = (*stack)->prev;
	free(*stack);
	*stack = temp;
}


/**
* pint - print the top of the stack
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
		_exiterr(stack, "L%u: can't pint, stack empty\n", line_number);
	printf("%d\n", (*stack)->n);
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
