#ifndef __UTIL_HEADER__
#define __UTIL_HEADER__

#include <stdarg.h>

void print_char(va_list list_print, int *characters_printed);
void print_string(va_list list_print, int *characters_printed,
									int left_justified);

void print_percent(int *characters_printed);
void print_percent(int *characters_printed);
void handle_format_specifier(const char **format, va_list list_print,
														 int *characters_printed);
void print_binary(va_list list_print, int *characters_printed);
void print_unsigned_int(va_list list_print, int *characters_printed,
												unsigned int base);

void print_unsigned_integer(va_list list_print, int *characters_printed,
														char length_modifier, int base, int uppercase);
/* we alreadt have a print_string definition */
void print_str_hex(char *str, int *printed_chars);
void print_pointer(va_list list_print, int *characters_printed);
void handle_format_specifier_lowercase(const char **format, va_list list_print,
																			 int *characters_printed);
void handle_format_specifier_uppercase(const char **format, va_list list_print,
																			 int *characters_printed);
void handle_format_specifier_other_characters(const char **format,
																							va_list list_print,
																							int *characters_printed);
void print_pointer_address(va_list list_print, int *characters_printed);
void print_unknown(char unknown, int *characters_printed);
char *rot13(char *message);
void handle_str_reverse_modifier(va_list list_print, int *characters_printed);
char *str_reverse(char *str);
void handle_ouxX(va_list list_print, int *characters_printed, char length_modifier,
								 char conversion_specifier);
#endif