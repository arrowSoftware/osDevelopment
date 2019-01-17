#include "string.h"
#include "../cpu/types.h"
#include "../drivers/screen.h"

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

void hexToAscii(int argNumber, char argStr[])
{
    char zeros = 0;
    int tmp;
    int i;

    append(argStr, '0');
    append(argStr, 'x');

    for (i = 28; i > 0; i -= 4)
    {
        tmp = (argNumber >> i) & 0xF;
        if (tmp == 0 && zeros == 0)
        {
            continue;
        }
        zeros = 1;

        if (tmp > 0xA)
        {
            append(argStr, tmp - 0xA + 'a');
        }
        else
        {
            append(argStr, tmp + '0');
        }
    }

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

void append(char argStr[], char argChar)
{
    int len = strlen(argStr);
    argStr[len] = argChar;
    argStr[len+1] = '\0';
}

void backspace(char argStr[])
{
    int len = strlen(argStr);
    argStr[len-1] = '\0';
}

 /* Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int strcmp(char argStr1[], char argStr2[]) {
    int i;
    for (i = 0; argStr1[i] == argStr2[i]; i++) {
        if (argStr1[i] == '\0') return 0;
    }
    return argStr1[i] - argStr2[i];
}
