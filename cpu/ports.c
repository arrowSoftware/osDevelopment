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

u8 portByteIn(u16 argPort)
{
    u8 result;

    /*
     * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
     * '"d" (port)': map the C variable '(port)' into e'd'x register
     */
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (argPort));
    return result;
}

void portByteOut(u16 argPort, u8 argData)
{
   /*
    * Notice how here both registers are mapped to C variables and
    * nothing is returned, thus, no equals '=' in the asm syntax
    * However we see a comma since there are two variables in the input area
    * and none in the 'return' area
    */
    __asm__ __volatile__("out %%al, %%dx" : : "a" (argData), "d" (argPort));
}

u16 portWordIn(u16 argPort)
{
    u16 result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (argPort));
    return result;
}

void portWordOut(u16 argPort, u16 argData)
{
    __asm__ __volatile__("out %%ax, %%dx" : : "a" (argData), "d" (argPort));
}
