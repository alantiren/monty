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
char *n;
int value;
stack_t *new_node;
n = strtok(NULL, " \t\n");
if (n == NULL || !is_numeric(n))
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
exit(EXIT_FAILURE);
}
value = atoi(n);
new_node = malloc(sizeof(stack_t));
if (new_node == NULL)
{
fprintf(stderr, "Error: malloc failed\n");
free_stack(*stack);
exit(EXIT_FAILURE);
}
new_node->n = value;
new_node->prev = NULL;
if (*stack != NULL)
{
new_node->next = *stack;
(*stack)->prev = new_node;
}
*stack = new_node;
}

/**
 * pall - Implements the pall opcode.
 * @stack: Double pointer to the top of the stack.
 * @line_number: The line number where the pall opcode appears.
 *
 * Description: The pall opcode prints all the values on the stack,
 * starting from the top of the stack.
 * If the stack is empty, nothing is printed.
 */

void pall(stack_t **stack)
{
stack_t *current = *stack;
while (current != NULL)
{
printf("%d\n", current->n);
current = current->next;
}
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
 * an error message is printed
 * and the program exits with EXIT_FAILURE.
 *
 * Return: EXIT_SUCCESS upon successful execution, EXIT_FAILURE otherwise.
 */

int main(int argc, char *argv[])
{
FILE *fp;
char *line = NULL;
unsigned int line_number = 0;
stack_t *stack = NULL;
char *opcode;
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
while (fgets(line, sizeof(line), fp) != NULL)
{
line_number++;
opcode = strtok(line, " \t\n");
if (opcode != NULL && opcode[0] != '#')
{
if (strcmp(opcode, "push") == 0)
{
char *arg = strtok(NULL, " \t\n");
if (arg == NULL || !is_numeric(arg))
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
free(line);
free_stack(stack);
fclose(fp);
exit(EXIT_FAILURE);
}
push(&stack, atoi(arg));
}
else if (strcmp(opcode, "pall") == 0)
{
pall(&stack);
}
else
{
fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
free(line);
free_stack(stack);
fclose(fp);
exit(EXIT_FAILURE);
}
}
}
free(line);
free_stack(stack);
fclose(fp);
return (EXIT_SUCCESS);
}
