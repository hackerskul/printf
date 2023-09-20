#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...) {
    va_list args;
    int i;
    int chars_printed;
    va_start(args, format);

    chars_printed = 0;

    for (i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            if (format[i] == '\0') break;

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
                    chars_printed += snprintf(NULL, 0, "%d", num);

                    break;
                }
                case '%':
                    putchar('%');
                    chars_printed++;
                    break;
                default:
		    putchar('%');
		    putchar(format[i]);
                    chars_printed += 10;
            }
        } else {
            putchar(format[i]);
            chars_printed++;
        }
    }

    va_end(args);
    return chars_printed;
}
