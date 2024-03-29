#include "monty.h"
#include <stdlib.h>

/**
* add - add the top two elements of the stack
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->prev == NULL)
		_exiterr(stack, "L%u: can't add, stack too short\n", line_number);
	temp = (*stack)->prev;
	temp->n += (*stack)->n;
	temp->next = NULL;
	free(*stack);
	*stack = temp;
}

/**
* sub - subtract the top two elements of the stack
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->prev == NULL)
		_exiterr(stack, "L%u: can't sub, stack too short\n", line_number);
	temp = (*stack)->prev;
	temp->n -= (*stack)->n;
	temp->next = NULL;
	free(*stack);
	*stack = temp;
}

/**
* _div - divide the top two elements of the stack
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void _div(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->prev == NULL)
		_exiterr(stack, "L%u: can't div, stack too short\n", line_number);
	if ((*stack)->n == 0)
		_exiterr(stack, "L%u: division by zero\n", line_number);
	temp = (*stack)->prev;
	temp->n /= (*stack)->n;
	temp->next = NULL;
	free(*stack);
	*stack = temp;
}

/**
* mul - multiply the top two elements of the stack
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->prev == NULL)
		_exiterr(stack, "L%u: can't mul, stack too short\n", line_number);
	temp = (*stack)->prev;
	temp->n *= (*stack)->n;
	temp->next = NULL;
	free(*stack);
	*stack = temp;
}

/**
* nop - does nothing
* @stack: pointer to the top of the stack
* @line_number: the line number of the instruction
* Return: Nothing
*/
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack, (void)line_number;
}
