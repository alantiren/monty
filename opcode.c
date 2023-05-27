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
 *
 * Return: 0 if opcode executed successfully, -1 on failure
 */

int execute_opcode(const char *opcode, stack_t **stack,
unsigned int line_number)
{
if (opcode == NULL || opcode[0] == '#')
return (0);
if (strcmp(opcode, "push") == 0)
push(stack, line_number);
else if (strcmp(opcode, "pall") == 0)
pall(stack, line_number);
else if (strcmp(opcode, "pint") == 0)
pint(stack, line_number);
else if (strcmp(opcode, "pop") == 0)
pop(stack, line_number);
else if (strcmp(opcode, "swap") == 0)
swap(stack, line_number);
else if (strcmp(opcode, "add") == 0)
add(stack, line_number);
else if (strcmp(opcode, "nop") == 0)
nop(stack, line_number);
else if (strcmp(opcode, "sub") == 0)
sub(stack, line_number);
else if (strcmp(opcode, "div") == 0)
div_op(stack, line_number);
else if (strcmp(opcode, "mul") == 0)
mul(stack, line_number);
else if (strcmp(opcode, "mod") == 0)
mod(stack, line_number);
else if (strcmp(opcode, "pchar") == 0)
pchar(stack, line_number);
else if (strcmp(opcode, "pstr") == 0)
pstr(stack, line_number);
else if (strcmp(opcode, "rotl") == 0)
rotl(stack);
else if (strcmp(opcode, "rotr") == 0)
rotr(stack);
else if (strcmp(opcode, "stack") == 0)
set_mode(stack, 1, 0);
else if (strcmp(opcode, "queue") == 0)
set_mode(stack, 0, 1);
else
fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
return (-1);

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
