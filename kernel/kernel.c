#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "shell.h"

void kernelMain()
{
    clearScreen();
    isrInstall();
    irqInstall();

    asm("int $2");
    asm("int $3");

    shellInit();

    kprint("Type something, it will go through the kernel\n"
           "Type END to halt the CPU\n> ");
}

void userInput(char *argInput)
{
    if (strcmp(argInput, "END") == 0)
    {
        kprint("Stopping the CPU\n");
        asm volatile("hlt");
    }
    else if (strcmp(argInput, "PAGE") == 0)
    {
        uint32_t physicalAddr;
        uint32_t page = kmalloc(1000, 1, &physicalAddr);
        char pageStr[16] = "";
        htoa(page, pageStr);
        char physicalAddrStr[16] = "";
        htoa(physicalAddr, physicalAddrStr);
        kprint("page: ");
        kprint(pageStr);
        kprint(", physical address: ");
        kprint(physicalAddrStr);
        kprint("\n");
    }

    kprint("echo: ");
    kprint(argInput);
    kprint("\n");
}
