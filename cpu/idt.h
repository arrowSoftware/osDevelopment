#ifndef _IDT_H_
#define _IDT_H_

#include "types.h"

/* Segment selectors */
#define KERNEL_CS 0x08

/* How every interrupt gate (handler) is defined */
typedef struct
{
    u16 lowOffset; /*lower 16 bits of handler function address. */
    u16 select;    /* Kernel segment selector. */
    u8 always0;
    /*
     * First byte.
     * Bits 7: "Interrupt is present"
     * Bits 6-5: priviledge level of caller (0 = kernel..3 = user)
     * Bit 4: set to 0 for interrupt gates.
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate"
     */
     u8 flags;
     u16 highOffset; /* Higher 16 bits of handler function address. */
} __attribute__((packed)) idt_gate_t;


/* A pointer to the array of interrupt handlers. Assembly instruction lidt reads this. */
typedef struct
{
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idtReg;

void setIdtGate(int argGate, u32 argHandler);
void setIdt();

#endif /* _IDT_H_ */
