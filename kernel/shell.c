#include "shell.h"
#include "../libc/string.h"
#include "../libc/stdio.h"

void shellInit(void)
{
    printf("%s\n", "shellInit");
}

void shell(void)
{
    char command[256];

    while(strcmp(command, "EXIT") != 0)
    {

    }
}
