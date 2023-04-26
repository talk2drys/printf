#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * print_binary - utility function that is used by a printing a %b
 * character to the standard output stream.
 *
 * @list_print: a variable of type va_list that holds the list of
 * arguments to be printed. This parameter is used to retrieve the
 * character to be printed from the argument list.
 *
 * @characters_printed: a pointer to an integer that keeps track of
 * the number of characters printed so far. This parameter is used to
 * update the count of characters printed.
 *
 * Returns: void
 **/
void print_binary(va_list list_print, int *characters_printed)
{
	unsigned int number = va_arg(list_print, unsigned int);
	int i, remainder;
	/* the maximum binary digit that can be store in an int*/
	int binary[2147483647];

	for (i = 0; number > 0 && i < 2147483647; i++)
	{
		remainder = number % 2;
		binary[i] = remainder;
		number = number / 2;
	}

	for (i = i - 1; i >= 0; i--)
	{
		char c = binary[i] + '0';

		write(STDOUT_FILENO, &c, 1);
		(*characters_printed)++;
	}
}
