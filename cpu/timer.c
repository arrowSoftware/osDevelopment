#include "timer.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"
#include "isr.h"

u32 tick = 0;

static void timerCallback(registers_t argRegs)
{
    char tickAscii[256];

    tick++;
    kprint("ticks: ");
    intToAscii(tick, tickAscii);
    kprint(tickAscii);
    kprint("\n");
}

void initTimer(u32 argFrequency)
{
    u32 divisor;
    u32 low;
    u32 high;

    /* Install the timer callback function. */
    registerInterruptHandler(IRQ0, timerCallback);

    /* Get the PIT value: haardware clock at 1193180 Hz. */
    divisor = 1193180 / argFrequency;
    low = (u8)(divisor & 0xFF);
    high = (u8)((divisor >> 8) & 0xFF);

    /* Send the command. */
    portByteOut(0x43, 0x36); /* Command port. */
    portByteOut(0x40, low);
    portByteOut(0x40, high);
}
