#include "util.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * print_pointer - prints the memory address of a pointer
 *
 * @list_print: the va_list that contains the pointer to print
 * @characters_printed: a pointer to the number of characters printed so far
 *
 * Return: void
 */
void print_pointer(va_list list_print, int *characters_printed)
{
	print_unsigned_int(list_print, characters_printed, 16);
}


void handle_format_specifier_other_characters(const char **format, va_list list_print,
									   int *characters_printed)
{
	switch (**format)
		{
		case '%':
			print_percent(characters_printed);
			(*format)++;
			break;
		default:
			(*format)++;
		}
}
