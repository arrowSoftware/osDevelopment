#include "./stdio.h"
#include "../drivers/screen.h"
#include "stdarg.h"

void printf(char *argFormat, ...)
{
    char *s;
    va_list lst;
    va_start(lst, argFormat);

    while(*argFormat != '\0')
    {
        if(*argFormat != '%')
        {
            kprintChar(*argFormat);
            argFormat++;
            continue;
        }

        argFormat++;

        if(*argFormat == '\0')
        {
            break;
        }

        switch(*argFormat)
        {
            case 's': kprint(va_arg(lst, char *)); break;
            case 'c': kprintChar(va_arg(lst, int)); break;
        }
        argFormat++;
    }
}
