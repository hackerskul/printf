#include "main.h"

/**
 * calculateWidth - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @currentIndex: Current index of the format string
 * @args: List of arguments to be printed.
 *
 * Return: Width.
 */
int calculateWidth(const char *format, int *currentIndex, va_list args)
{
    int currIndex;
    int width = 0;

    for (currIndex = *currentIndex + 1; format[currIndex] != '\0'; currIndex++)
    {
        if (is_digit(format[currIndex]))
        {
            width *= 10;
            width += format[currIndex] - '0';
        }
        else if (format[currIndex] == '*')
        {
            currIndex++;
            width = va_arg(args, int);
            break;
        }
        else
        {
            break;
        }
    }

    *currentIndex = currIndex - 1;
    return width;
}
