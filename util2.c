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
	int *binary = (int *)malloc(sizeof(int) * 32);

	if (!binary)
		return;

	if (number == 0)
	{
		char c = '0';
		write(STDOUT_FILENO, &c, 1);
		fflush(stdout);
		(*characters_printed)++;
		return;
	}

	for (i = 0; number > 0 && i < 32; i++)
	{
		remainder = number % 2;
		binary[i] = remainder;
		number = number / 2;
	}

	for (i = i - 1; i >= 0; i--)
	{
		char c = binary[i] + '0';

		write(STDOUT_FILENO, &c, 1);
		fflush(stdout);
		(*characters_printed)++;
	}

	free(binary);
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
	fflush(stdout);
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
			fflush(stdout);
			(*printed_chars)++;
		}
		else
		{
			putchar('\\');
			putchar('x');
			putchar((*str / 16) < 10 ? (*str / 16) + '0' : (*str / 16) - 10 + 'A');
			putchar((*str % 16) < 10 ? (*str % 16) + '0' : (*str % 16) - 10 + 'A');
			fflush(stdout);
			(*printed_chars) += 4;
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
	case 'R':
	{
		char *text = va_arg(list_print, char *);
		char *rot13_string = rot13(text);

		write(STDOUT_FILENO, rot13_string, strlen(rot13_string));
		fflush(stdout);
		(*characters_printed) += strlen(rot13_string);
		(*format)++;
		break;
	}
	default:
		print_unknown(**format, characters_printed);
		(*format)++;
	}
}

/**
 * rot13 - encodes a string using rot13
 * @message: string to encode
 * Return: encoded string
 */
char *rot13(char *message)
{
	size_t i;

	size_t len = strlen(message);
	char *output = (char *)malloc(len + 1);
	char *outptr = output;

	for (i = 0; i < len; i++)
	{
		if (*message >= 'a' && *message <= 'z')
		{
			int h = (*message - 'a' + 13) % 26 + 'a';
			*outptr = h;
		}
		else if (*message >= 'A' && *message <= 'Z')
		{
			*outptr = (*message - 'A' + 13) % 26 + 'A';
		}
		else
		{
			*outptr = *message;
		}
		message++;
		outptr++;
	}
	*outptr = '\0';
	return (output);
}
