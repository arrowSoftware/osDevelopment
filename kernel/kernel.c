#include "../drivers/screen.h"

void main()
{
    int i = 0;

    clearScreen();

    for (i = 0; i < 24; i++)
    {
        char str[255];
        intToAscii(i, str);
        kprintAt(str, 0, i);
    }

    kprintAt("This text forces the kernel to scroll. Row 0 will disappear. ", 60, 24);
    kprint("And with this text, the kernel will scroll again, and row 1 will disappear too!");
}
