#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "monty.h"

/**
 * sub - Subtracts the top element of the stack from the second top element
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 */

void sub(stack_t **stack, unsigned int line_number)
{
int result;

if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
result = (*stack)->next->n - (*stack)->n;
pop(stack, line_number);
(*stack)->n = result;
}

/**
 * div_op - Divides the second top element of the stack by the top element
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 *
 * Description: The div opcode divides the second top element of the stack
 * by the top element of the stack. The result is stored in the second top
 * element, and the top element is removed. If the stack contains less than
 * two elements, or if the top element is 0, an error message is printed
 * and the program exits with EXIT_FAILURE status.
 */

void div_op(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
exit(EXIT_FAILURE);
}

if ((*stack)->n == 0)
{
fprintf(stderr, "L%u: division by zero\n", line_number);
exit(EXIT_FAILURE);
}

(*stack)->next->n /= (*stack)->n;
pop(stack, line_number);
}

/**
 * mul - Multiplies the second top element of the stack with the top element
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 *
 * Description: The mul opcode multiplies the second top element of the stack
 * with the top element of the stack. The result is stored in the second top
 * element, and the top element is removed. If the stack contains less than
 * two elements, an error message is printed and the program exits with
 * EXIT_FAILURE status.
 */

void mul(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
exit(EXIT_FAILURE);
}

(*stack)->next->n *= (*stack)->n;
pop(stack, line_number);
}

/**
 * mod - Computes the rest of the division of the second top element
 *          of the stack by the top element
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the opcode in the file
 *
 * Description: The mod opcode computes the rest of the division of the
 * second top element of the stack by the top element. The result is stored
 * in the second top element, and the top element is removed. If the stack
 * contains less than two elements or if the top element is 0, an error
 * message is printed and the program exits with EXIT_FAILURE status.
 */

void mod(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
if ((*stack)->n == 0)
{
fprintf(stderr, "L%u: division by zero\n", line_number);
exit(EXIT_FAILURE);
}
(*stack)->next->n %= (*stack)->n;
pop(stack, line_number);
}

/**
 * pchar - Prints the character at the top of the stack
 * @stack: Double pointer to the stack
 * @line_number: Line number of the opcode
 */

void pchar(stack_t **stack, unsigned int line_number)
{
int value = (*stack)->n;
if (*stack == NULL)
{
fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
exit(EXIT_FAILURE);
}
if (value < 0 || value > 127)
{
fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
exit(EXIT_FAILURE);
}
printf("%c\n", value);
}
