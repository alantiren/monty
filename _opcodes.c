#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
int result;

if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
result = (*stack)->next->n - (*stack)->n;
pop(stack, line_number);
(*stack)->n = result;
}


/**
 * div_op - Divides the second top element of the stack by the top element
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 *
 * Description: The div opcode divides the second top element of the stack
 * by the top element of the stack. The result is stored in the second top
 * element, and the top element is removed. If the stack contains less than
 * two elements, or if the top element is 0, an error message is printed
 * and the program exits with EXIT_FAILURE status.
 */

void div_op(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
exit(EXIT_FAILURE);
}

if ((*stack)->n == 0)
{
fprintf(stderr, "L%u: division by zero\n", line_number);
exit(EXIT_FAILURE);
}

(*stack)->next->n /= (*stack)->n;
pop(stack, line_number);
}

/**
 * mul - Multiplies the second top element of the stack with the top element
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 *
 * Description: The mul opcode multiplies the second top element of the stack
 * with the top element of the stack. The result is stored in the second top
 * element, and the top element is removed. If the stack contains less than
 * two elements, an error message is printed and the program exits with
 * EXIT_FAILURE status.
 */

void mul(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
exit(EXIT_FAILURE);
}

(*stack)->next->n *= (*stack)->n;
pop(stack, line_number);
}

/**
 * mod - Computes the rest of the division of the second top element
 *          of the stack by the top element
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 *
 * Description: The mod opcode computes the rest of the division of the
 * second top element of the stack by the top element. The result is stored
 * in the second top element, and the top element is removed. If the stack
 * contains less than two elements or if the top element is 0, an error
 * message is printed and the program exits with EXIT_FAILURE status.
 */

void mod(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
if ((*stack)->n == 0)
{
fprintf(stderr, "L%u: division by zero\n", line_number);
exit(EXIT_FAILURE);
}
(*stack)->next->n %= (*stack)->n;
pop(stack, line_number);
}

/**
 * pchar - Prints the character at the top of the stack
 * @stack: Double pointer to the stack
 * @line_number: Line number of the opcode
 */

void pchar(stack_t **stack, unsigned int line_number)
{
int value = (*stack)->n;
if (*stack == NULL)
{
fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
exit(EXIT_FAILURE);
}
if (value < 0 || value > 127)
{
fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
exit(EXIT_FAILURE);
}
printf("%c\n", value);
}

/**
 * pstr - Prints the string starting at the top of the stack, followed by a newline
 * @stack: Double pointer to the head of the stack
 * @line_number: Line number of the opcode being executed
 */

void pstr(stack_t **stack, unsigned int line_number)
{
stack_t *current = *stack;
(void)line_number;

while (current != NULL && current->n != 0 && current->n >= 0 && current->n <= 127)
{
printf("%c", current->n);
current = current->next;
}
printf("\n");
}

/**
 * rotl - Rotates the stack to the top
 * @stack: Double pointer to the stack
 * @line_number: Line number of the opcode
 */

void rotl(stack_t **stack)
{
stack_t *first = *stack;
stack_t *second = (*stack)->next;

if (*stack != NULL && (*stack)->next != NULL)
{
while (first->next != NULL)
first = first->next;

first->next = *stack;
(*stack)->prev = first;
*stack = second;
second->prev = NULL;
first->next->next = NULL;
}
}

/**
 * rotr - Rotates the stack to the bottom
 * @stack: Double pointer to the stack
 * @line_number: Line number of the opcode
 */

void rotr(stack_t **stack)
{
stack_t *last = *stack;
stack_t *second_last;

if (*stack != NULL && (*stack)->next != NULL)
{
while (last->next != NULL)
last = last->next;

second_last = last->prev;

last->prev = NULL;
last->next = *stack;
(*stack)->prev = last;
*stack = last;

if (second_last != NULL)
second_last->next = NULL;
}
}
