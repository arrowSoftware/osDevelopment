#include "utils.h"

void memoryCopy(char *argSource, char *argDestination, int argNumBytes)
{
    int i;

    for (i = 0; i < argNumBytes; i++)
    {
        *(argDestination + i) = *(argSource + i);
    }
}

void memorySet(u8 *argDestination, u8 argValue, u32 argLength)
{
    u8 *temp = argDestination;

    for (; argLength != 0; argLength--)
    {
        *temp++ = argValue;
    }
}

void intToAscii(int argNumber, char argStr[])
{
    int i;
    int sign;

    if ((sign = argNumber) < 0)
    {
        argNumber = -argNumber;
    }

    i = 0;

    do
    {
        argStr[i++] = argNumber % 10 + '0';
    } while ((argNumber /= 10) > 0);

    if (sign < 0)
    {
        argStr[i++] = '-';
    }

    argStr[i] = '\0';

    reverse(argStr);
}

void reverse(char argStr[])
{
    int c, i, j;

    for(i = 0, j = strlen(argStr) - 1;
        i < j;
        i++, j--)
        {
            c = argStr[i];
            argStr[i] = argStr[j];
            argStr[j] = c;
        }
}

int strlen(char argStr[])
{
    int i = 0;

    while (argStr[i] != '\0')
    {
        ++i;
    }

    return i;
}
