#include "main.h"
Certainly! Here's the rewritten code for the get_width and handle_print functions:

c

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

/**
 * handlePrint - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @args: List of arguments to be printed.
 * @currentIndex: Current index of the format string.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: Get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed or -1 on error.
 */
int handlePrint(const char *format, int *currentIndex, va_list args, char buffer[],
                int flags, int width, int precision, int size)
{
    int i, unknownLen = 0, printedChars = -1;

    fmt_t fmtTypes[] = {
        {'c', printChar},     {'s', printString},       {'%', printPercent},
        {'i', printInt},      {'d', printInt},          {'b', printBinary},
        {'u', printUnsigned}, {'o', printOctal},        {'x', printHexadecimal},
        {'X', printHexaUpper}, {'p', printPointer},     {'S', printNonPrintable},
        {'r', printReverse},  {'R', printRot13String}, {'\0', NULL}};

    for (i = 0; fmtTypes[i].fmt != '\0'; i++)
    {
        if (format[*currentIndex] == fmtTypes[i].fmt)
            return fmtTypes[i].fn(args, buffer, flags, width, precision, size);
    }

    if (fmtTypes[i].fmt == '\0')
    {
        if (format[*currentIndex] == '\0')
            return -1;

        unknownLen += write(1, "%", 1);

        if (format[*currentIndex - 1] == ' ')
            unknownLen += write(1, " ", 1);
        else if (width)
        {
            (*currentIndex)--;
            while (format[*currentIndex] != ' ' && format[*currentIndex] != '%')
                (*currentIndex)--;
            if (format[*currentIndex] == ' ')
                (*currentIndex)--;
            return 1;
        }

        unknownLen += write(1, &format[*currentIndex], 1);
        return unknownLen;
    }

    return printedChars;
}
