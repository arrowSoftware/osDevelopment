#include "idt.h"
#include "../kernel/utils.h"

void setIdtGate(int argGate, u32 argHandler)
{
    idt[argGate].lowOffset = LOW_16(argHandler);
    idt[argGate].select = KERNEL_CS;
    idt[argGate].always0 = 0;
    idt[argGate].flags = 0x8E;
    idt[argGate].highOffset = HIGH_16(argHandler);
}

void setIdt()
{
    idtReg.base = (u32)&idt;
    idtReg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    __asm__ __volatile__("lidtl (%0)" : : "r" (&idtReg));
}
