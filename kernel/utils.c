void memoryCopy(char *argSource, char *argDestination, int argNumBytes)
{
    int i;

    for (i = 0; i < argNumBytes; i++)
    {
        *(argDestination + i) = *(argSource + i);
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
}
