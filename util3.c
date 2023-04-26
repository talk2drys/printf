#include "util.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define True 1
#define False 0


/**
 * print_pointer_address - prints the memory address of a pointer
 *
 * @list_print: the va_list that contains the pointer to print
 * @characters_printed: a pointer to the number of characters printed so far
 *
 * return: void
 */
void print_pointer_address(va_list list_print, int *characters_printed)
{
	void *ptr = va_arg(list_print, void *);
	char buffer[20];
	int len = snprintf(buffer, sizeof(buffer), "%p", ptr);

	write(STDOUT_FILENO, buffer, len);
	(*characters_printed) += len;
}


/**
 * print_unknown - print unknow specifier as is
 *
 * @unknown: the unknow specifier character
 * @characters_printed: a pointer to the number of characters printed so far
 *
 * return: void
 */
void print_unknown(char unknown, int *characters_printed)
{
	write(STDOUT_FILENO, &"%", 1);
	write(STDOUT_FILENO, &unknown, 1);

	(*characters_printed)++;
}

/**
 * print_unsigned - print unknow specifier as is
 *
 * @list_print: the va_list that contains the pointer to print
 * @characters_printed: a pointer to the number of characters printed so far
 * @base: number base to use
 * @uppercase: specify if the specifier is an upper case letter example 'x' 'X'
 * return: void
 */
void print_unsigned_integer(va_list list_print, int *characters_printed, int base,
					int uppercase)
{
	char buffer[20];
	unsigned int number = va_arg(list_print, unsigned int);
	int digit, i = 0;
	char format = uppercase ? 'A' : 'a';

	if (number == 0)
	{
		buffer[i++] = '0';
	}
	else
	{
		while (number != 0)
		{
			digit = number % base;
			buffer[i++] =
				digit < 10 ? '0' + digit : format + digit - 10;
			number /= base;
		}
	}

	while (--i >= 0)
	{
		write(STDOUT_FILENO, &buffer[i], 1);
		(*characters_printed)++;
	}
}

void handle_format_specifier_other_characters(const char **format,
											  __attribute__((unused)) va_list list_print,
											  int *characters_printed)
{
	switch (**format)
	{
	case '%':
		print_percent(characters_printed);
		(*format)++;
		break;
	default:
		print_unknown(**format, characters_printed);
		(*format)++;
	}
}
