#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

#define BUFF_SIZE 1024
#define UNUSED(x) (void)(x)

/* Flag values for formatting */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* Size specifiers */
#define S_LONG 1
#define S_SHORT 2

/* Structure to store format types and their corresponding functions */
typedef struct fmt_type
{
    char fmt;
    int (*fn)(va_list, char[], int, int, int, int);
} fmt_t;

int _printf(const char *format, ...);
int print_char(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_string(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_percent(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_int(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_binary(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_unsigned(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_octal(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_hexadecimal(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_hexa_upper(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_pointer(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_non_printable(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_reverse(va_list list, char buffer[], int flags, int width, int precision, int size);
int print_rot13string(va_list list, char buffer[], int flags, int width, int precision, int size);

int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
                 int flags, int width, int precision, int size);

void print_buffer(char buffer[], int *buff_ind);
int is_printable(char c);
int append_hexa_code(char ascii_code, char buffer[], int i);
int is_digit(char c);
long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */

