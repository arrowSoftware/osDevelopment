#include "mem.h"

void memoryCopy(u8 *argSource, u8 *argDestination, int argNumBytes)
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
