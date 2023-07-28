#include "main.h"

/**
 * calculateActiveFlags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @currentIndex: Current index of the format string
 * Return: Flags:
 */
int calculateActiveFlags(const char *format, int *currentIndex)
{
    /* - + 0 # ' ' */
    /* 1 2 4 8  16 */
    int j, currIndex;
    int flags = 0;
    const char FLAGS_CHARACTERS[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_VALUES[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    for (currIndex = *currentIndex + 1; format[currIndex] != '\0'; currIndex++)
    {
        for (j = 0; FLAGS_CHARACTERS[j] != '\0'; j++)
        {
            if (format[currIndex] == FLAGS_CHARACTERS[j])
            {
                flags |= FLAGS_VALUES[j];
                break;
            }
        }

        if (FLAGS_CHARACTERS[j] == 0)
            break;
    }

    *currentIndex = currIndex - 1;
    return flags;
}

