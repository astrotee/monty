#include "monty.h"
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

