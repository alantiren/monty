#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "monty.h"

#define MAX_LINE_LENGTH 1000

/**
 * is_numeric - Check if a string represents a numeric value
 * @str: The string to check
 *
 * Return: 1 if the string is numeric, 0 otherwise
 */

int is_numeric(const char *str)
{
int i;
for (i = 0; str[i] != '\0'; i++)
{
if (i == 0 && str[i] == '-')
continue;
if (str[i] < '0' || str[i] > '9')
return (0);
}
return (1);
}

/**
 * push - Pushes an element to the stack
 * @stack: Pointer to the stack
 * @line_number: Line number of the opcode in the file
 */

void push(stack_t **stack, unsigned int line_number)
{
char *arg = strtok(NULL, " \t\n");
int value;
if (arg == NULL || !is_numeric(arg))
{
fprintf(stderr, "L%d: usage: push integer\n", line_number);
exit(EXIT_FAILURE);
}

value = atoi(arg);
if (push_node(stack, value) == NULL)
{
fprintf(stderr, "Error: malloc failed\n");
exit(EXIT_FAILURE);
}
}

/**
 * pall - Implements the pall opcode.
 * @stack: Double pointer to the top of the stack.
 *@line_number: Line number of the opcode being executed
 */

void pall(stack_t **stack, unsigned int line_number)
{
stack_t *current = *stack;

(void)line_number;

while (current != NULL)
{
printf("%d\n", current->n);
current = current->next;
}
}

/**
 * push_node - Pushes a new node to the stack
 * @stack: Double pointer to the head of the stack
 * @value: Value to be pushed
 * Return: Pointer to the newly added node, or NULL on failure
 */
stack_t *push_node(stack_t **stack, int value)
{
stack_t *new_node = malloc(sizeof(stack_t));
if (new_node == NULL)
return (NULL);

new_node->n = value;
new_node->prev = NULL;
new_node->next = *stack;

if (*stack != NULL)
(*stack)->prev = new_node;

*stack = new_node;
return (new_node);
}
