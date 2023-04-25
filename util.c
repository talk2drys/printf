#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * print_char - utility function that is used by a printing a single
 * character to the standard output stream. It takes two parameters:
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
	(*characters_printed)++;
}

/**
 * print_string - utility function that is used by a printing an array
 * of characters to the standard output stream. It takes two parameters:
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
void print_string(va_list list_print, int *characters_printed)
{
	char *string = va_arg(list_print, char *);

	write(STDOUT_FILENO, string, strlen(string));
	(*characters_printed) += strlen(string);
}

/**
 * print_percent - utility function that is used by a printing a %
 * character to the standard output stream. It takes two parameters:
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

	(*characters_printed)++;
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
void handle_format_specifier(const char **format, va_list list_print,
							 int *characters_printed)
{
	switch (**format)
		{
		case 'c':
			print_char(list_print, characters_printed);
			(*format)++;
			break;

		case 's':
			print_string(list_print, characters_printed);
			(*format)++;
			break;

		case '%':
			print_percent(characters_printed);
			(*format)++;
			break;
		}
}
