#include "timer.h"
#include "../drivers/screen.h"
#include "../cpu/ports.h"
#include "isr.h"
#include "../libc/function.h"

uint32_t tick = 0;

static void timerCallback(registers_t *argRegs)
{
    tick++;
    UNUSED(argRegs);
}

void initTimer(uint32_t argFrequency)
{
    uint32_t divisor;
    uint32_t low;
    uint32_t high;

    /* Install the timer callback function. */
    registerInterruptHandler(IRQ0, timerCallback);

    /* Get the PIT value: haardware clock at 1193180 Hz. */
    divisor = 1193180 / argFrequency;
    low = (uint8_t)(divisor & 0xFF);
    high = (uint8_t)((divisor >> 8) & 0xFF);

    /* Send the command. */
    portByteOut(0x43, 0x36); /* Command port. */
    portByteOut(0x40, low);
    portByteOut(0x40, high);
}
