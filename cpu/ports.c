/* +---+--------------------+ */
/* | r |    Register(s)     | */
/* +---+--------------------+ */
/* | a |   %eax, %ax, %al   | */
/* | b |   %ebx, %bx, %bl   | */
/* | c |   %ecx, %cx, %cl   | */
/* | d |   %edx, %dx, %dl   | */
/* | S |   %esi, %si        | */
/* | D |   %edi, %di        | */
/* +---+--------------------+ */
/* The IN instruction reads from an I/O device, OUT writes. */

#include "ports.h"

uint8_t portByteIn(uint16_t argPort)
{
    uint8_t result;

    /*
     * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
     * '"d" (port)': map the C variable '(port)' into e'd'x register
     */
    asm("in %%dx, %%al" : "=a" (result) : "d" (argPort));
    return result;
}

void portByteOut(uint16_t argPort, uint8_t argData)
{
   /*
    * Notice how here both registers are mapped to C variables and
    * nothing is returned, thus, no equals '=' in the asm syntax
    * However we see a comma since there are two variables in the input area
    * and none in the 'return' area
    */
    asm volatile("out %%al, %%dx" : : "a" (argData), "d" (argPort));
}

uint16_t portWordIn(uint16_t argPort)
{
    uint16_t result;
    asm("in %%dx, %%ax" : "=a" (result) : "d" (argPort));
    return result;
}

void portWordOut(uint16_t argPort, uint16_t argData)
{
    asm volatile("out %%ax, %%dx" : : "a" (argData), "d" (argPort));
}
