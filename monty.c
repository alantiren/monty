#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

/**
 * is_numeric - Checks if a string is a valid integer.
 * @str: The string to check.
 *
 * Return: 1 if the string is a valid integer, 0 otherwise.
 */
int is_numeric(const char *str)
{
    if (str == NULL || *str == '\0')
        return (0);

    int i = 0;
    if (str[0] == '-')

        i++;

    for (; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')  // Checking each character
            return (0);
    }

    return (1);
}

/**
 * push - Implements the push opcode.
 * @stack: Double pointer to the top of the stack.
 * @line_number: The line number where the push opcode appears.
 *
 * Description: The push opcode pushes an element to the stack.
 * The argument to push must be an integer.
 * If the argument is not an integer or if there is no argument given,
 * an error message is printed and the program exits with EXIT_FAILURE.
 * The push operation allocates memory for a new node and adds it to the stack.
 */
void push(stack_t **stack, unsigned int line_number)
{
    char *arg = strtok(NULL, " \t\n");

    if (arg == NULL || !is_numeric(arg))
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    stack_t *new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = atoi(arg);  // Converting the argument to an integer
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack != NULL)
        (*stack)->prev = new_node;

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
void pall(stack_t **stack, unsigned int line_number)
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
 * If an unknown opcode is encountered or an error occurs, an error message is printed
 * and the program exits with EXIT_FAILURE.
 *
 * Return: EXIT_SUCCESS upon successful execution, EXIT_FAILURE otherwise.
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    stack_t *stack = NULL;

    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;

    while (getline(&line, &len, fp) != -1)
    {
        line_number++;

        char *opcode = strtok(line, " \t\n");

        if (opcode != NULL)
        {
            if (strcmp(opcode, "push") == 0)
                push(&stack, line_number);
            else if (strcmp(opcode, "pall") == 0)
                pall(&stack, line_number);
            else
            {
                fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(fp);
    free(line);

    return (EXIT_SUCCESS);
}
