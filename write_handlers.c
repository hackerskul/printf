#include "main.h"

/************************* WRITE HANDLE *************************/

/**
 * handleWriteChar - Prints a char
 * @c: Char types.
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags.
 * @width: Get width.
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */

int handleWriteChar(char c, char buffer[], int flags, int width, int precision, int size)
{
    /* Char is stored at the left and padding at buffer's right */
    int i = 0;
    char padd = ' ';

    UNUSED(precision);
    UNUSED(size);

    if (flags & F_ZERO)
        padd = '0';

    buffer[i++] = c;
    buffer[i] = '\0';

    if (width > 1)
    {
        buffer[BUFF_SIZE - 1] = '\0';

        for (i = 0; i < width - 1; i++)
            buffer[BUFF_SIZE - i - 2] = padd;

        if (flags & F_MINUS)
            return write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - i - 1], width - 1);
        else
            return write(1, &buffer[BUFF_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1);
    }

    return write(1, &buffer[0], 1);
}

/************************* WRITE NUMBER *************************/

/**
 * writeNumber - Prints a number
 * @isNegative: Flag indicating if the number is negative
 * @ind: Char types.
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Get width.
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */

int writeNumber(int isNegative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1;
    char padd = ' ', extraCh = 0;

    UNUSED(size);

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';

    if (isNegative)
        extraCh = '-';
    else if (flags & F_PLUS)
        extraCh = '+';
    else if (flags & F_SPACE)
        extraCh = ' ';

    return writeNum(ind, buffer, flags, width, precision, length, padd, extraCh);
}

/**
 * writeNum - Write a number using a buffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: Width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Padding char
 * @extraCh: Extra char
 *
 * Return: Number of printed chars.
 */

int writeNum(int ind, char buffer[], int flags, int width, int prec, int length, char padd, char extraCh)
{
    int i, paddStart = 1;

    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
        return 0; /* printf(".0d", 0)  no char is printed */

    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
    {
        buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
    }

    if (prec > 0 && prec < length)
    {
        padd = ' ';
    }

    while (prec > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    if (extraCh != 0)
    {
        length++;
    }

    if (width > length)
    {
        for (i = 1; i < width - length + 1; i++)
        {
            buffer[i] = padd;
        }

        buffer[i] = '\0';

        if (flags & F_MINUS && padd == ' ') /* Assign extra char to the left of buffer */
        {
            if (extraCh)
            {
                buffer[--ind] = extraCh;
            }

            return write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1);
        }
        else if (!(flags & F_MINUS) && padd == ' ') /* Extra char to the left of buffer */
        {
            if (extraCh)
            {
                buffer[--ind] = extraCh;
            }

            return write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length);
        }
        else if (!(flags & F_MINUS) && padd == '0') /* Extra char to the left of padd */
        {
            if (extraCh)
            {
                buffer[--paddStart] = extraCh;
            }

            return write(1, &buffer[paddStart], i - paddStart) +
                   write(1, &buffer[ind], length - (1 - paddStart));
        }
    }

    if (extraCh)
    {
        buffer[--ind] = extraCh;
    }

    return write(1, &buffer[ind], length);
}

/**

 * writeUnsigned - Writes an unsigned number
 * @isNegative: Number indicating if the number is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */

int writeUnsigned(int isNegative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    /* The number is stored at the buffer's right and starts at position i */
    int length = BUFF_SIZE - ind - 1, i = 0;
    char padd = ' ';

    UNUSED(isNegative);
    UNUSED(size);

    if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        return 0; /* printf(".0d", 0)  no char is printed */

    if (precision > 0 && precision < length)
        padd = ' ';

    while (precision > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';

    if (width > length)
    {
        for (i = 0; i < width - length; i++)
            buffer[i] = padd;

        buffer[i] = '\0';

        if (flags & F_MINUS) /* Assign extra char to the left of buffer [buffer > padd] */
        {
            return write(1, &buffer[ind], length) + write(1, &buffer[0], i);
        }
        else /* Assign extra char to the left of padding [padd > buffer] */
        {
            return write(1, &buffer[0], i) + write(1, &buffer[ind], length);
        }
    }

    return write(1, &buffer[ind], length);
}

/**
 * writePointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extraCh: Char representing extra char
 *
 * Return: Number of written chars.
 */

int writePointer(char buffer[], int ind, int length, int width, int flags, char padd, char extraCh)
{
    int i;

    if (width > length)
    {
        for (i = 3; i < width - length + 3; i++)
            buffer[i] = padd;

        buffer[i] = '\0';

        if (flags & F_MINUS && padd == ' ') /* Assign extra char to the left of buffer */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';

            if (extraCh)
                buffer[--ind] = extraCh;

            return write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3);
        }
        else if (!(flags & F_MINUS) && padd == ' ') /* Extra char to the left of buffer */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';

            if (extraCh)
                buffer[--ind] = extraCh;

            return write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length);
        }
        else if (!(flags & F_MINUS) && padd == '0') /* Extra char to the left of padd */
        {
            buffer[1] = '0';
            buffer[2] = 'x';

            if (extraCh)
                buffer[--ind] = extraCh;

            return write(1, &buffer[ind], BUFF_SIZE - ind - 1);
        }
    }

    buffer[--ind] = 'x';
    buffer[--ind] = '0';

    if (extraCh)
        buffer[--ind] = extraCh;

    return write(1, &buffer[ind], BUFF_SIZE - ind - 1);
}

