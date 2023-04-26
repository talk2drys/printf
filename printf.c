#include "util.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STRING_NULL_TERMINATION '\0'
#define BASE_10 10

/**
 * _printf - custom implementation of the standard C library function
 * printf that takes a format string and a variable number of
 * arguments and prints them to standard output.
 *
 * @format: format string
 *
 * Return: Return: number of characters printed
 **/
int _printf(const char *format, ...)
{
	va_list list_print;
	int characters_printed = 0;

	va_start(list_print, format);

	while (*format != STRING_NULL_TERMINATION)
	{
		if (*format == '%')
		{
			format++;
			if (*format >= 'a' && *format <= 'z')
			{
				handle_format_specifier_lowercase(
					&format, list_print, &characters_printed);
			}
			else if (*format >= 'A' && *format <= 'Z')
			{
				handle_format_specifier_uppercase(
					&format, list_print, &characters_printed);
			}
			else
			{
				handle_format_specifier_other_characters(
					&format, list_print, &characters_printed);
			}
		}
		else
		{
			char buffer = *format;

			write(STDOUT_FILENO, &buffer, 1);
			format++;
			characters_printed++;
		}
	}

	va_end(list_print);
	return (characters_printed);
}
