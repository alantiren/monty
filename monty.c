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

/**
 * main - Entry point of the Monty interpreter.
 * @argc: The number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Description: The main function reads the Monty byte code file,
 * executes the corresponding opcodes, and handles errors.
 * It creates and initializes the stack, reads each line of the file,
 * tokenizes the line to extract the opcode, and executes the opcode function.
 * If an unknown opcode is encountered or an error occurs,
 * an error message is printed and the program exits with EXIT_FAILURE.
 *
 * Return: EXIT_SUCCESS upon successful execution, EXIT_FAILURE otherwise.
 */

int main(int argc, char *argv[])
{
FILE *fp;

if (argc != 2)
{
fprintf(stderr, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}
fp = fopen(argv[1], "r");
if (fp == NULL)
{
fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
exit(EXIT_FAILURE);
}
if (process_file(fp) == -1)
{
fclose(fp);
exit(EXIT_FAILURE);
}
fclose(fp);
return (EXIT_SUCCESS);
}
