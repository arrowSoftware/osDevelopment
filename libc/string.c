/*******************************************************************************
 * File:
 *  string.h
 *
 * Description:
 *  This file contains functions to work with strings. Specfically character
 *  arrays.
 *
 * Members:
 *  strcmp
 *  append
 *  strlen
 *  reverse
 *  backspace
 *  intToAscii
 *  hexToAscii
 *
 * Todo:
 *  Update strcmp to check the sizes of each argument to compare entire string.
 *
 * Modification History:
 *  Date         Who         Description
 *  ============================================================================
 *  01/17/19    T.Gajewski   Initial version.
 ******************************************************************************/
#include "string.h"
#include "../cpu/types.h"

int strcmp(char argStr1[], char argStr2[])
{
    /* Loop interator. */
    int i;

    /*
     * Loop over the characer array checking for equal values. Skip over the
     * loop if the strings dont match, otherwise keeo going to null terminator.
     */
    for (i = 0; argStr1[i] == argStr2[i]; i++)
    {
        /* If end of string was found inside argStr1, then return match. */
        if (argStr1[i] == '\0')
        {
            return 0;
        }
    }

    /* Strings do not match so return the difference. */
    return argStr1[i] - argStr2[i];
}

void itoa(int argNumber, char argStr[])
{
    /* Interator */
    int i = 0;

    /* Is the number signed. */
    int sign = argNumber;

    /* If the number is less than 0 apply the sign. */
    if (sign < 0)
    {
        argNumber = -argNumber;
    }

    /*
     * Get each digit from the number and add the offset to ascii '0' to it, to
     * get the numbers ascii value. Then remove a digit and repeat.
     */
    do
    {
        argStr[i++] = argNumber % 10 + '0';
    } while ((argNumber /= 10) > 0);

    /* If the number is signed, less than 0, add the negative symbol. */
    if (sign < 0)
    {
        argStr[i++] = '-';
    }

    /* Add a null terminator. */
    argStr[i] = '\0';

    /* reverse the string into the correct order. */
    reverse(argStr);
}

void htoa(int argNumber, char argStr[])
{
    /* Hoe many zeros to add. */
    char zeros = 0;

    /* Temporary holder. */
    int tmp;

    /* Iterator. */
    int i;

    /* Append the '0x' to the string. */
    append(argStr, '0');
    append(argStr, 'x');

    /*
     * Loop over top lower 28 bits and grab the shorts from the number to
     * convert so a single ascii hex value.
     */
    for (i = 28; i > 0; i -= 4)
    {
        /* Grab the short from the number. */
        tmp = (argNumber >> i) & 0xF;

        if (tmp == 0 && zeros == 0)
        {
            continue;
        }

        zeros = 1;

        /*
         * If the remp value is greater then 9 then we need to print some
         * letters.  Add the ascii A to the number to get the number ascii value.
         */
        if (tmp >= 0xA)
        {
            append(argStr, tmp - 0xA + 'A');
        }
        /* Other wise print the ascii decimal value. */
        else
        {
            append(argStr, tmp + '0');
        }
    }

    /* Do the same thing as above for the final 4 bits. */
    tmp = argNumber & 0xF;
    if (tmp >= 0xA)
    {
        append(argStr, tmp - 0xA + 'a');
    }
    else
    {
        append(argStr, tmp + '0');
    }
}

void reverse(char argStr[])
{
    /* Hold the temp character to reverse. */
    int tempChar;

    /* Loop interator upward. */
    int i;

    /* Loop iterator downward. */
    int j;

    /* i starts at the first character in the string, j starts at the last. */
    for(i = 0, j = strlen(argStr) - 1;
        i < j;
        i++, j--)
        {
            /* Store the character move. */
            c = argStr[i];

            /* swap the saved character and the jth char. */
            argStr[i] = argStr[j];
            argStr[j] = c;
        }
}

int strlen(char argStr[])
{
    /* Iterator. */
    int i = 0;

    /* Increment the iterator until we reach the null terminator. */
    while (argStr[i] != '\0')
    {
        ++i;
    }

    return i;
}

void append(char argStr[], char argChar)
{
    /* Store the size of the string. */
    int len = strlen(argStr);

    /*
     * length returns the number of characters in 1-base, so add the new
     * character at the end.
     */
    argStr[len] = argChar;

    /* Add the null terminator. */
    argStr[len + 1] = '\0';
}

void backspace(char argStr[])
{
    /* Store the length of the string. */
    int len = strlen(argStr);

    /*
     * replace the last non null terminator with a null terminator so remove
     * last char.
     */
    argStr[len-1] = '\0';
}
