#include <stdlib.h>
#include "monty.h"

/**
 * free_stack - Frees all the nodes in a stack.
 * @stack: Pointer to the top of the stack.
 *
 * Description: This function frees all the nodes in a stack,
 * starting from the top of the stack and working its way down.
 * It releases the memory allocated for each node and updates the
 * pointers accordingly.
 */

void free_stack(stack_t **stack)
{
stack_t *current = *stack;
stack_t *next;

while (current != NULL)
{
next = current->next;
free(current);
current = next;
}

*stack = NULL;
}

/**
 * pop - Removes the top element from the stack
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 *
 * Description: The pop function removes the top element from the stack,
 * updates the stack pointer,
 * and frees the memory allocated for the removed element.
 * If the stack is empty,
 * an error message is printed and the program exits with EXIT_FAILURE.
 */
void pop(stack_t **stack, unsigned int line_number)
{
stack_t *temp;

if (*stack == NULL)
{
fprintf(stderr, "L%u: can't pop from an empty stack\n", line_number);
exit(EXIT_FAILURE);
}
temp = *stack;
*stack = (*stack)->next;
if (*stack != NULL)
(*stack)->prev = NULL;
free(temp);
}
