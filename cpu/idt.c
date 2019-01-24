/*******************************************************************************
 * File:
 *
 *
 * Description:
 *
 *
 * Members:
 *
 * Todo:
 *
 *
 * Modification History:
 *  Date         Who         Description
 *  ============================================================================
 *  01/17/19    T.Gajewski   Initial version.
 ******************************************************************************/

#include "idt.h"

void setIdtGate(int argGate, uint32_t argHandler)
{
    idt[argGate].lowOffset = LOW_16(argHandler);
    idt[argGate].select = KERNEL_CS;
    idt[argGate].always0 = 0;
    idt[argGate].flags = 0x8E;
    idt[argGate].highOffset = HIGH_16(argHandler);
}

void setIdt()
{
    idtReg.base = (uint32_t)&idt;
    idtReg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    asm volatile("lidtl (%0)" : : "r" (&idtReg));
}
