#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "monty.h"

/**
 * pstr - Prints the string starting at
 * the top of the stack, followed by a newline
 * @stack: Double pointer to the head of the stack
 * @line_number: Line number of the opcode being executed
 */

void pstr(stack_t **stack, unsigned int line_number)
{
stack_t *current = *stack;

(void)line_number;

while (current != NULL && current->n != 0 && isascii(current->n))
{
putchar(current->n);
current = current->next;
}

putchar('\n');
}

/**
 * rotl - Rotates the stack to the top
 * @stack: Double pointer to the stack
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
