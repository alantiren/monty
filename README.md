# Monty ByteCode Interpreter

This is a Monty byte code interpreter implemented in C.

## Requirements

- Ubuntu 20.04 LTS
- GCC compiler
- Editor: vi, vim, or emacs

## Compilation

To compile the interpreter, run the following command:
$ gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty

## Usage

To run the interpreter, use the following command:
$ ./monty <file>

Replace `<file>` with the path to the Monty byte code file you want to execute.

## Monty Byte Code Files

Monty byte code files contain instructions to manipulate a stack. Each instruction is written on a separate line.

Example Monty byte code file:
push 1
push 2
push 3
pall

## Supported Opcodes

- `push <int>`: Pushes an integer onto the stack.
- `pall`: Prints all the values on the stack.

## Error Handling

The interpreter handles various error cases, including:
- Invalid instructions
- Empty stack
- Insufficient arguments

## License

This project is licensed under the [MIT License](LICENSE).