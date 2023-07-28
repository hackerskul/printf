#include "main.h"

/**
 * calculatePrecision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @currentIndex: Current index of the format string
 * @args: List of arguments to be printed.
 *
 * Return: Precision.
 */
int calculatePrecision(const char *format, int *currentIndex, va_list args)
{
    int currIndex = *currentIndex + 1;
    int precision = -1;

    if (format[currIndex] != '.')
        return precision;

    precision = 0;

    for (currIndex += 1; format[currIndex] != '\0'; currIndex++)
    {
        if (is_digit(format[currIndex]))
        {
            precision *= 10;
            precision += format[currIndex] - '0';
        }
        else if (format[currIndex] == '*')
        {
            currIndex++;
            precision = va_arg(args, int);
            break;
        }
        else
        {
            break;
        }
    }

    *currentIndex = currIndex - 1;
    return precision;
}

