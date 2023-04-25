#ifndef __UTIL_HEADER__
#define __UTIL_HEADER__

#include <stdarg.h>

void print_char(va_list list_print, int *characters_printed);
void print_string(va_list list_print, int *characters_printed);
void print_percent(int *characters_printed);
void handle_format_specifier(const char **format, va_list list_print,
							 int *characters_printed);

#endif
