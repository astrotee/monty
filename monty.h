#ifndef MONTY_H
#define MONTY_H
#define _GNU_SOURCE
#define ISIZE 4
#include <stdio.h>

/**
 * struct global_object_s - global struct to keep track of used pointer
 * @oparg: the operation argument
 * @err: if an err occured
 * @line: the read line
 * @file: the read file
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct global_object_s
{
		char *oparg;
		short err;
		char *line;
		FILE *file;
} global_object;

extern global_object gb;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
		int n;
		struct stack_s *prev;
		struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
		char *opcode;
		void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


void freestack(stack_t **stack);
void clean(stack_t **stack);
void _exiterr(stack_t **stack, char *msg, ...);
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);

#endif
