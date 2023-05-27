#include "monty.h"

/**
 * stack_format - Sets the format of the data to stack (LIFO)
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 */

void stack_format(stack_t **stack, unsigned int line_number)
{
(void)stack;
(void)line_number;

}

/**
 * queue_format - Sets the format of the data to queue (FIFO)
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 */

void queue_format(stack_t **stack, unsigned int line_number)
{
stack_t *current = *stack;
stack_t *prev = NULL;

(void)line_number;

if (*stack == NULL || (*stack)->next == NULL)
return;

while (current->next != NULL)
{
prev = current;
current = current->next;
}

current->next = *stack;
(*stack)->prev = current;

*stack = (*stack)->next;
(*stack)->prev = NULL;

prev->next = NULL;

}
