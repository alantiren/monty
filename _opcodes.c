#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

/**
 * pint - Prints the value at the top of the stack
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 */

void pint(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL)
{
fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
exit(EXIT_FAILURE);
}

printf("%d\n", (*stack)->n);
}

/**
 * pop - Removes the top element of the stack
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 */

void pop(stack_t **stack, unsigned int line_number)
{
stack_t *temp;
if (*stack == NULL)
{
fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
free_stack(*stack);
exit(EXIT_FAILURE);
}
temp = *stack;
*stack = (*stack)->next;
if (*stack != NULL)
(*stack)->prev = NULL;
free(temp);
}

/**
 * swap - Swaps the top two elements of the stack
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 */
void swap(stack_t **stack, unsigned int line_number)
{
int temp;

if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
free_stack(*stack);
exit(EXIT_FAILURE);
}

temp = (*stack)->n;
(*stack)->n = (*stack)->next->n;
(*stack)->next->n = temp;
}

/**
 * add - Adds the top two elements of the stack
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 */

void add(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
free_stack(*stack);
exit(EXIT_FAILURE);
}
(*stack)->next->n += (*stack)->n;
pop(stack, line_number);
}

/**
 * nop - Does nothing
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 */

void nop(stack_t **stack, unsigned int line_number)
{
(void)stack;
(void)line_number;
}

/**
 * sub - Subtracts the top element of the stack from the second top element
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 */

void sub(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
int result = (*stack)->next->n - (*stack)->n;
pop(stack, line_number);
(*stack)->n = result;
}
