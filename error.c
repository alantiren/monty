#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * print_usage_error - Prints the usage error message.
 */
void print_usage_error(void)
{
	fprintf(stderr, "USAGE: monty file\n");
	exit(EXIT_FAILURE);
}

/**
 * print_file_open_error - Prints the file open error message.
 * @filename: The name of the file that couldn't be opened.
 */
void print_file_open_error(const char *filename)
{
	fprintf(stderr, "Error: Can't open file %s\n", filename);
	exit(EXIT_FAILURE);
}

/**
 * print_unknown_instruction_error - Prints the unknown instruction error message.
 * @line_number: The line number where the unknown instruction appears.
 * @opcode: The unknown opcode.
 */
void print_unknown_instruction_error(unsigned int line_number, const char *opcode)
{
	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}

/**
 * print_push_argument_error - Prints the push argument error message.
 * @line_number: The line number where the push argument error occurs.
 */
void print_push_argument_error(unsigned int line_number)
{
	fprintf(stderr, "L%u: usage: push integer\n", line_number);
	exit(EXIT_FAILURE);
}

/**
 * print_malloc_error - Prints the malloc error message.
 */
void print_malloc_error(void)
{
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
}
