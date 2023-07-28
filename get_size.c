#include "main.h"

/**
 * calculateSize - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @currentIndex: Current index of the format string
 *
 * Return: Size.
 */
int calculateSize(const char *format, int *currentIndex)
{
    int currIndex = *currentIndex + 1;
    int size = 0;

    if (format[currIndex] == 'l')
    {
        size = S_LONG;
    }
    else if (format[currIndex] == 'h')
    {
        size = S_SHORT;
    }

    if (size == 0)
    {
        *currentIndex = currIndex - 1;
    }
    else
    {
        *currentIndex = currIndex;
    }

    return size;
}

