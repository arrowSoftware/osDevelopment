/*******************************************************************************
 * File:
 *  timer.h
 *
 * Description:
 *  This file contains code to start a registers an ISR with the cpu timer.
 *
 * Members:
 *  initTimer()
 *
 * Todo:
 *  None.
 *
 * Modification History:
 *  Date         Who         Description
 *  ============================================================================
 *  01/17/19    T.Gajewski   Initial version.
 ******************************************************************************/

#include "timer.h"
#include "../drivers/screen.h"
#include "../cpu/ports.h"
#include "isr.h"
#include "../libc/function.h"

uint32_t tick = 0;

/* A generic timer that does nothing. Todo: make this do something. */
static void timerCallback(registers_t *argRegs)
{
    tick++;
    UNUSED(argRegs);
}

void initTimer(uint32_t argFrequency)
{
    uint32_t divisor = 0;
    uint32_t low = 0;
    uint32_t high = 0;
    uint8_t pitCmd = (PIT_CMD_CHAN_0  |
                     PIT_CMD_LO_HI    |
                     PIT_CMD_SQR_WAVE |
                     PIT_CMD_BIN_MODE);

    /* The Programmable Interval Timer (PIT) chip */
    /* Install the timer callback function. */
    registerInterruptHandler(IRQ0, timerCallback);

    /* Get the PIT value: haardware clock at 1193180 Hz. */
    divisor = 1193180 / argFrequency;
    low = (uint8_t)(divisor & 0xFF);
    high = (uint8_t)((divisor >> 8) & 0xFF);

    /* Send the command. */
    portByteOut(PIT_COMMAND, pitCmd);
    portByteOut(PIT_CHAN_0_DATA, low);
    portByteOut(PIT_CHAN_0_DATA, high);
}
