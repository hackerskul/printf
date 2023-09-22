#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...) {
    va_list args;
    int count;
    va_start(args, format);

    count = 0;

    while (*format) {
        char c;
        const char *str;
        int num;
        unsigned int unum;
        void *ptr;

        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c':
                    c = va_arg(args, int);
                    putchar(c);
                    count++;
                    break;
                case 's':
                    str = va_arg(args, const char *);
                    while (*str) {
                        putchar(*str);
                        count++;
                        str++;
                    }
                    break;
                case '%':
                    putchar('%');
                    count++;
                    break;
                case 'd':
                    num = va_arg(args, int);
                    printf("%d", num);
                    count += snprintf(NULL, 0, "%d", num);
                    break;
                case 'u':
                    unum = va_arg(args, unsigned int);
                    printf("%u", unum);
                    count += snprintf(NULL, 0, "%u", unum);
                    break;
                case 'o':
                    unum = va_arg(args, unsigned int);
                    printf("%o", unum);
                    count += snprintf(NULL, 0, "%o", unum);
                    break;
                case 'x':
                    unum = va_arg(args, unsigned int);
                    printf("%x", unum);
                    count += snprintf(NULL, 0, "%x", unum);
                    break;
                case 'p':
                    ptr = va_arg(args, void *);
                    printf("%p", ptr);
                    count += snprintf(NULL, 0, "%p", ptr);
                    break;
                case 'l':
                    num = count;
                    printf("%d", num);
                    count += snprintf(NULL, 0, "%d", num);
                    break;
                default:
                    putchar('%');
                    count++;
                    putchar(*format);
                    count++;
                    break;
            }
        } else {
            putchar(*format);
            count++;
        }
        format++;
    }

    va_end(args);
    return count;
}
