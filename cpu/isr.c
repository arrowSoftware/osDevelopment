#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"
#include "../drivers/ports.h"

isr_t interrruptHandlers[256];

void isrInstall()
{
    setIdtGate(0, (u32)isr0);
    setIdtGate(1, (u32)isr1);
    setIdtGate(2, (u32)isr2);
    setIdtGate(3, (u32)isr3);
    setIdtGate(4, (u32)isr4);
    setIdtGate(5, (u32)isr5);
    setIdtGate(6, (u32)isr6);
    setIdtGate(7, (u32)isr7);
    setIdtGate(8, (u32)isr8);
    setIdtGate(9, (u32)isr9);
    setIdtGate(10, (u32)isr10);
    setIdtGate(11, (u32)isr11);
    setIdtGate(12, (u32)isr12);
    setIdtGate(13, (u32)isr13);
    setIdtGate(14, (u32)isr14);
    setIdtGate(15, (u32)isr15);
    setIdtGate(16, (u32)isr16);
    setIdtGate(17, (u32)isr17);
    setIdtGate(18, (u32)isr18);
    setIdtGate(19, (u32)isr19);
    setIdtGate(20, (u32)isr20);
    setIdtGate(21, (u32)isr21);
    setIdtGate(22, (u32)isr22);
    setIdtGate(23, (u32)isr23);
    setIdtGate(24, (u32)isr24);
    setIdtGate(25, (u32)isr25);
    setIdtGate(26, (u32)isr26);
    setIdtGate(27, (u32)isr27);
    setIdtGate(28, (u32)isr28);
    setIdtGate(29, (u32)isr29);
    setIdtGate(30, (u32)isr30);
    setIdtGate(31, (u32)isr31);

    /* Remap the PIC. */
    portByteOut(MASTER_PIC_COMMAND, 0x11);
    portByteOut(SLAVE_PIC_COMMAND, 0x11);
    portByteOut(MASTER_PIC_DATA, 0x20);
    portByteOut(SLAVE_PIC_DATA, 0x28);
    portByteOut(MASTER_PIC_DATA, 0x04);
    portByteOut(SLAVE_PIC_DATA, 0x02);
    portByteOut(MASTER_PIC_DATA, 0x01);
    portByteOut(SLAVE_PIC_DATA, 0x01);
    portByteOut(MASTER_PIC_DATA, 0x0);
    portByteOut(SLAVE_PIC_DATA, 0x0);

    setIdtGate(32, (u32)irq0);
    setIdtGate(33, (u32)irq1);
    setIdtGate(34, (u32)irq2);
    setIdtGate(35, (u32)irq3);
    setIdtGate(36, (u32)irq4);
    setIdtGate(37, (u32)irq5);
    setIdtGate(38, (u32)irq6);
    setIdtGate(39, (u32)irq7);
    setIdtGate(40, (u32)irq8);
    setIdtGate(41, (u32)irq9);
    setIdtGate(42, (u32)irq10);
    setIdtGate(43, (u32)irq11);
    setIdtGate(44, (u32)irq12);
    setIdtGate(45, (u32)irq13);
    setIdtGate(46, (u32)irq14);
    setIdtGate(47, (u32)irq15);

    setIdt();
}

/* To print the message which defines every exception */
char *exceptionMessages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isrHandler(registers_t argR)
{
    char s[3];
    kprint("received interrrupt: ");
    intToAscii(argR.intNumber, s);
    kprint(s);
    kprint("\n");
    kprint(exceptionMessages[argR.intNumber]);
    kprint("\n");
}

void registerInterruptHandler(u8 argIntNumber, isr_t argHandler)
{
    interrruptHandlers[argIntNumber] = argHandler;
}

void irqHandler(registers_t argReg)
{
    /*
     * After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again
     */
     if (argReg.intNumber >= 40)
     {
         portByteOut(SLAVE_PIC_COMMAND, 0x20); /* Slave. */
     }

     portByteOut(MASTER_PIC_COMMAND, 0x20); /* Master. */

     if (interrruptHandlers[argReg.intNumber] != 0)
     {
         isr_t handler = interrruptHandlers[argReg.intNumber];
         handler(argReg);
     }
}
