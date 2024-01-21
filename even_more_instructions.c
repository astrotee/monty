#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
* mod - modulus of the top two elements of the stack
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->prev == NULL)
		_exiterr(stack, "L%u: can't mod, stack too short\n", line_number);
	if ((*stack)->n == 0)
		_exiterr(stack, "L%u: division by zero\n", line_number);
	temp = (*stack)->prev;
	temp->n %= (*stack)->n;
	temp->next = NULL;
	free(*stack);
	*stack = temp;
}

/**
* pchar - print the top of the stack as a character
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void pchar(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
		_exiterr(stack, "L%u: can't pchar, stack empty\n", line_number);
	if ((*stack)->n & 0xFFFFFF80)
		_exiterr(stack, "L%u: can't pchar, value out of range\n", line_number);
	printf("%c\n", (*stack)->n);
}

/**
* pstr - print the values of the stack as a string
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *cur = gb.FIFO ? gb.tail : *stack;
	(void)line_number;

	while (cur)
	{
		if (cur->n == 0 || cur->n & 0xFFFFFF80)
			break;
		printf("%c", cur->n);
		cur = gb.FIFO ? cur->next : cur->prev;
	}
	printf("\n");
}

/**
* rotl - rotate the stack to the top
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack, *tail = *stack;
	(void)line_number;

	while (tail && tail->prev)
		tail = tail->prev;
	if (tail == top)
		return;
	*stack = top->prev;
	top->prev->next = NULL;
	top->prev = NULL;
	top->next = tail;
	tail->prev = top;
}

/**
* rotr - rotate the stack to the bottom
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack, *tail = *stack;
	(void)line_number;

	while (tail && tail->prev)
		tail = tail->prev;
	if (tail == top)
		return;
	*stack = tail;
	tail->next->prev = NULL;
	tail->next = NULL;
	tail->prev = top;
	top->next = tail;
}
