#include "util.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * print_char - utility function that is used by a printing a single
 * character to the standard output stream.
 *
 * @list_print: a variable of type va_list that holds the list of
 * arguments to be printed
 *
 * @characters_printed: a pointer to an integer that keeps track
 * of the number of characters printed so far. This parameter
 * is used to update the count of characters printed.
 *
 * Returns: void
 **/
void print_char(va_list list_print, int *characters_printed)
{
	char character = (char)va_arg(list_print, int);

	write(STDOUT_FILENO, &character, 1);
	fflush(stdout);
	(*characters_printed)++;
}

/**
 * print_string - utility function that is used by a printing an array
 * of characters to the standard output stream.
 *
 * @list_print: a variable of type va_list that holds the list of
 * arguments to be printed. This parameter is used to retrieve the
 * character to be printed from the argument list.
 *
 * @characters_printed: a pointer to an integer that keeps track of
 * the number ofcharacters printed so far. This parameter is used
 * to update the count of characters printed.
 *
 * Returns: void
 **/
void print_string(va_list list_print, int *characters_printed,
									int left_justified)
{
	char *string = va_arg(list_print, char *);
	size_t string_len = strlen(string);
	size_t padding = 0;

	if (string == NULL)
	{
		write(STDOUT_FILENO, "(null)", 6);
		(*characters_printed) += 6;
		return;
	}

	if (left_justified)
	{
		write(STDOUT_FILENO, string, string_len);
		(*characters_printed) += string_len;
		padding = left_justified - string_len;
	}
	else
	{
		padding = left_justified - string_len;
		for (size_t i = 0; i < padding; i++)
		{
			write(STDOUT_FILENO, " ", 1);
			(*characters_printed)++;
		}
		write(STDOUT_FILENO, string, string_len);
		(*characters_printed) += string_len;
	}

	fflush(stdout);
}

/**
 * print_percent - utility function that is used by a printing a %
 * character to the standard output stream. It takes two parameters
 *
 * @characters_printed: a pointer to an integer that keeps track of
 * the number of characters printed so far. This parameter is used to
 * update the count of characters printed.
 *
 * Returns: void
 **/
void print_percent(int *characters_printed)
{
	write(STDOUT_FILENO, &"%", 1);
	fflush(stdout);

	(*characters_printed)++;
}

/**
 * print_integer - utility function that is used by a printing a %d
 * and %1 character to the standard output stream.
 *
 * @list_print: a variable of type va_list that holds the list of
 * arguments to be printed. This parameter is used to retrieve the
 * character to be printed from the argument list.
 *
 * @characters_printed: a pointer to an integer that keeps track of
 * the number of characters printed so far.
 *
 * @length_modifier: l or h
 **/
void print_integer(va_list list_print, int *characters_printed, char length_modifier)
{
	long int long_integer = 0;
	short int short_integer = 0;
	int integer = 0;
	char buffer[20];

	switch (length_modifier)
	{
	case 'l':
		long_integer = va_arg(list_print, long int);
		snprintf(buffer, sizeof(buffer), "%lX", long_integer);
		break;
	case 'h':
		short_integer = va_arg(list_print, short int);
		snprintf(buffer, sizeof(buffer), "%hX", short_integer);
		break;
	default:
		integer = va_arg(list_print, int);
		snprintf(buffer, sizeof(buffer), "%X", integer);
		break;
	}

	write(STDOUT_FILENO, buffer, strlen(buffer));
	fflush(stdout);
	(*characters_printed) += strlen(buffer);
}

/*
*handle_format_specifier - utility function used to
 handle a format specifier encountered in the input string. It takes three
 parameters:

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
void handle_format_specifier_lowercase(const char **format, va_list list_print,
																			 int *characters_printed)
{
	char length_modifier = '\0';
	int left_justified = 0;

	if (**format == '-')
	{
		left_justified = 1;
		(*format)++;
	}

	if (**format == 'l' || **format == 'h')
	{
		length_modifier = **format;
		(*format)++;
	}

	switch (**format)
	{
	case 'c':
		print_char(list_print, characters_printed);
		break;
	case 's':
		print_string(list_print, characters_printed);
		break;
	case 'd':
	case 'i':
		print_integer(list_print, characters_printed, length_modifier);
		break;
	case 'b':
		print_binary(list_print, characters_printed);
		break;
	case 'p':
		print_pointer_address(list_print, characters_printed);
		break;
	case 'u':
	case 'o':
	case 'x':
		handle_ouxX(list_print, characters_printed, length_modifier, **format);
		break;
	case 'X':
		handle_ouxX(list_print, characters_printed, length_modifier, **format);
		break;
	case 'r':
		handle_str_reverse_modifier(list_print, characters_printed);
		break;
	default:
		print_unknown(**format, characters_printed);
		break;
	}
	(*format)++;
}
