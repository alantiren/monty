#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

while (current != NULL && current->n != 0)
{
if (current->n >= 0 && current->n <= 127)
printf("%c", current->n);
else
break;

current = current->next;
}
printf("\n");
}


/**
 * rotl - Rotates the stack to the top
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 */

void rotl(stack_t **stack, unsigned int line_number)
{
stack_t *current = *stack;

(void)line_number;

if (current == NULL || current->next == NULL)
return;

while (current->next != NULL)
current = current->next;

current->next = *stack;
(*stack)->prev = current;
*stack = (*stack)->next;
(*stack)->prev = NULL;
current->next->next = NULL;
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
