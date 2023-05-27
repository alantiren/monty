#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

#define MAX_LINE_LENGTH 1000

/**
 * execute_opcode - Executes the opcode function based on the given opcode
 * @opcode: The opcode to execute
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 * @opcode_map: Array of opcode-function mappings
 *
 * Return: 0 if opcode executed successfully, -1 on failure
 */

int execute_opcode(const char *opcode, stack_t **stack,
unsigned int line_number, opcode_mapping_t *opcode_map)
{
if (opcode == NULL || opcode[0] == '#')
return (0);
int i = 0;
while (opcode_map[i].opcode != NULL)
{
if (strcmp(opcode, opcode_map[i].opcode) == 0)
{
opcode_map[i].function(stack, line_number);
return (0);
}
i++;
}
fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
return (-1);
}

int main(void)
{
opcode_mapping_t opcode_map[] = {
{"push", push},
{"pall", pall},
{"pint", pint},
{"pop", pop},
{"swap", swap},
{"add", add},
{"nop", nop},
{"sub", sub},
{"div", div_op},
{"mul", mul},
{"mod", mod},
{"pchar", pchar},
{"pstr", pstr},
{"rotl", rotl},
{"rotr", rotr},
{"stack", set_mode},
{"queue", set_mode},
{NULL, NULL}
};
const char *opcode = "push";
unsigned int line_number = 1;
stack_t *stack = NULL;
execute_opcode(opcode, &stack, line_number, opcode_map);
return (0);
}


/**
 * set_mode - Sets the stack and queue modes.
 * @stack: Double pointer to the top of the stack.
 * @stack_mode_val: Value to set for stack mode
 * (non-zero for enabled, 0 for disabled).
 * @queue_mode_val: Value to set for queue mode
 * (non-zero for enabled, 0 for disabled).
 *
 * Description: This function updates
 * the values of the stack_mode and queue_mode
 * variables based on the provided parameters.
 * It allows enabling or disabling the
 * stack mode and queue mode in a centralized and reusable way.
 */

void set_mode(stack_t **stack, int stack_mode_val, int queue_mode_val)
{
int queue_mode = 0;
int stack_mode = 1;
(void)stack;

queue_mode += queue_mode_val;
stack_mode += stack_mode_val;

printf("queue_mode: %d\n", queue_mode);
printf("stack_mode: %d\n", stack_mode);
}

/**
 * process_file - Processes the Monty byte code file
 * @fp: Pointer to the file to process
 *
 * Return: 0 if file processed successfully, -1 on failure
 */

int process_file(FILE *fp)
{
char *line = malloc(MAX_LINE_LENGTH);
unsigned int line_number = 0;
stack_t *stack = NULL;
char *opcode;

if (line == NULL)
{
fprintf(stderr, "Error: malloc failed\n");
return (-1);
}
while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
{
line_number++;
if (line[0] == '#')
continue;
opcode = strtok(line, " \t\n");
if (opcode == NULL)
continue;
if (execute_opcode(opcode, &stack, line_number) == -1)
{
free(line);
free_stack(stack);
return (-1);
}
}

free(line);
free_stack(stack);
return (0);
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
