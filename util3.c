#include "util.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

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
	fflush(stdout);
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
	fflush(stdout);
	write(STDOUT_FILENO, &unknown, 1);
	fflush(stdout);

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
void print_unsigned_integer(va_list list_print, int *characters_printed, char length_modifier, int base, int uppercase)
{
	unsigned long long unsigned_integer = 0;
	unsigned int uinteger = 0;
	unsigned short int ushort_integer = 0;
	unsigned char uchar_integer = 0;
	char buffer[40];

	switch (length_modifier)
	{
	case 'l':
		if (base == 10)
			unsigned_integer = va_arg(list_print, unsigned long long);
		else
			uinteger = va_arg(list_print, unsigned int);
		break;
	case 'h':
		if (base == 10)
			ushort_integer = va_arg(list_print, unsigned int);
		else
			uchar_integer = va_arg(list_print, unsigned int) & 0xFF;
		break;
	default:
		uinteger = va_arg(list_print, unsigned int);
		break;
	}

	if (length_modifier == 'l' && base == 10)
		snprintf(buffer, sizeof(buffer), "%llu", unsigned_integer);
	else if (length_modifier == 'h' && base == 10)
		snprintf(buffer, sizeof(buffer), "%hu", ushort_integer);
	else if (length_modifier == 'h' && base != 10)
		snprintf(buffer, sizeof(buffer), "%hhX", uchar_integer);
	else if (base == 10)
		snprintf(buffer, sizeof(buffer), "%u", uinteger);
	else
		snprintf(buffer, sizeof(buffer), "%X", uinteger);

	if (uppercase)
	{
		for (int i = 0; i < strlen(buffer); i++)
		{
			buffer[i] = toupper(buffer[i]);
		}
	}

	write(STDOUT_FILENO, buffer, strlen(buffer));
	fflush(stdout);
	(*characters_printed) += strlen(buffer);
}

/**
 * handle_str_reverse_modifier - Reverses a string
 *
 * @list_print: A va_list of arguments to print
 * @characters_printed: A pointer to the total number of characters printed
 */
void handle_str_reverse_modifier(va_list list_print, int *characters_printed)
{
	char *string = va_arg(list_print, char *);
	char *rev = str_reverse(string);

	if (rev == NULL)
		return;

	write(STDOUT_FILENO, rev, strlen(rev));
	fflush(stdout);
	(*characters_printed) += strlen(rev);

	free(rev);
}

void handle_format_specifier_other_characters(const char **format,
																							__attribute__((unused))
																							va_list list_print,
																							int *characters_printed)
{
	switch (**format)
	{
	case '%':
		print_percent(characters_printed);
		(*format)++;
		break;
	case ' ':
		print_percent(characters_printed);
		(*format)++;
		break;
	default:
		print_unknown(**format, characters_printed);
		(*format)++;
	}
}
