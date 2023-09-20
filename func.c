#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int chars_printed = 0; // Count of characters printed

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++; // Move past '%'
            if (format[i] == '\0') break; // Avoid undefined behavior

            // Handle conversion specifiers
            switch (format[i]) {
                case 'c':
                    putchar(va_arg(args, int));
                    chars_printed++;
                    break;
                case 's': {
                    const char *str = va_arg(args, const char *);
                    while (*str) {
                        putchar(*str);
                        str++;
                        chars_printed++;
                    }
                    break;
                }
                case 'd':
                case 'i': {
                    int num = va_arg(args, int);
                    printf("%d", num);
                    chars_printed += snprintf(NULL, 0, "%d", num); // Calculate printed characters
                    break;
                }
                case '%':
                    putchar('%');
                    chars_printed++;
                    break;
                default:
                    putchar('%'); // Print the '%' character
                    putchar(format[i]); // Print the unknown specifier
                    chars_printed += 2;
            }
        } 
	else 
	{
            putchar(format[i]);
            chars_printed++;
        }
    }

    va_end(args);
    return (chars_printed);
}
