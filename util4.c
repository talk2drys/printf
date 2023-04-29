#include "util.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define CONVERSION_SPECIFIER_U 'u'
#define CONVERSION_SPECIFIER_O 'o'
#define CONVERSION_SPECIFIER_X 'x'
#define CONVERSION_SPECIFIER_X_UPPER 'X'

void handle_ouxX(va_list list_print, int *characters_printed, char length_modifier,
				 char conversion_specifier)
{
	if (conversion_specifier == CONVERSION_SPECIFIER_U)
	{
//		print_unsigned_integer(list_print, characters_printed, 10, 0);
		print_unsigned_integer(list_print, characters_printed, length_modifier, 10, 0);
	}
	else if (conversion_specifier == CONVERSION_SPECIFIER_O)
	{
		print_unsigned_integer(list_print, characters_printed, length_modifier, 8, 0);
	}
	else if (conversion_specifier == CONVERSION_SPECIFIER_X)
	{
		print_unsigned_integer(list_print, characters_printed, length_modifier, 16, 0);
	}
	else if (conversion_specifier == CONVERSION_SPECIFIER_X_UPPER)
	{
		print_unsigned_integer(list_print, characters_printed, length_modifier, 16, 1);
	}
}