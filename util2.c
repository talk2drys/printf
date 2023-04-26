#include "util.h"
#include <stdarg.h>
#include <stdint.h>
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

/**
 * str_reverse - reverses a null-terminated string in place.
 *
 * @str: The string to be reversed.
 *
 * Return: void
 */
void str_reverse(char *str)
{
	int i, j;
	char temp;

	for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}

void print_unsigned_int(va_list list_print, int *characters_printed,
						unsigned int base)
{
	unsigned int num = va_arg(list_print, unsigned int);
	char buffer[33];
	int i = 0;

	if (num == 0)
	{
		buffer[i++] = '0';
	}
	else
	{
		while (num != 0)
		{
			unsigned int digit = num % base;

			buffer[i++] = digit < 10 ? digit + '0' : digit + 'a' - 10;
			num /= base;
		}
	}

	buffer[i] = '\0';
	str_reverse(buffer);

	write(STDOUT_FILENO, buffer, strlen(buffer));
	(*characters_printed) += strlen(buffer);
}

/**
 * print_str_hex - Prints a string with non-printable characters in hexadecimal
 * format
 *
 * @str: The string to print
 * @printed_chars: A pointer to the running total of characters printed
 *
 * Return: void
 */
void print_str_hex(char *str, int *printed_chars)
{
	while (*str)
	{
		if (*str >= 32 && *str <= 126)
		{
			putchar(*str);
			(*printed_chars)++;
		}
		str++;
	}
}

/*
*handle_format_specifier_uppercase - utility function used to
 handle a format specifier encountered in the input string.
 for upter case letters.

 @format: a pointer to a pointer to a character string that represents the
 format specifier. This parameter is updated to point to the next character in
 the format string after the specifier.

 @list_print: a variable of type va_list that holds the list of arguments to b
 printed. This parameter is used to retrieve the argument(s) to be printed
 corresponding to the format specifier.

 @characters_printed: a pointer to an integer that keeps track of the number of
 characters printed so far. This parameter is used to update the count of
 characters printed

 Returns: void
 **/
void handle_format_specifier_uppercase(const char **format, va_list list_print,
									   int *characters_printed)
{
	switch (**format)
	{
	case 'X':
		print_unsigned_integer(list_print, characters_printed, 16, 1);
		(*format)++;
		break;
	case 'S':
		print_str_hex(va_arg(list_print, char *), characters_printed);
		(*format)++;
		break;
	default:
		print_unknown(**format, characters_printed);
		(*format)++;
	}
}

