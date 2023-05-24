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

void free_stack(stack_t *stack)
{
stack_t *current = stack;
stack_t *next;
while (current != NULL)
{
next = current->next;
free(current);
current = next;
}
}
