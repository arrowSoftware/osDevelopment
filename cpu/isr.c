#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../cpu/ports.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "../cpu/timer.h"

isr_t interrruptHandlers[256];

void isrInstall()
{
    setIdtGate(0, (uint32_t)isr0);
    setIdtGate(1, (uint32_t)isr1);
    setIdtGate(2, (uint32_t)isr2);
    setIdtGate(3, (uint32_t)isr3);
    setIdtGate(4, (uint32_t)isr4);
    setIdtGate(5, (uint32_t)isr5);
    setIdtGate(6, (uint32_t)isr6);
    setIdtGate(7, (uint32_t)isr7);
    setIdtGate(8, (uint32_t)isr8);
    setIdtGate(9, (uint32_t)isr9);
    setIdtGate(10, (uint32_t)isr10);
    setIdtGate(11, (uint32_t)isr11);
    setIdtGate(12, (uint32_t)isr12);
    setIdtGate(13, (uint32_t)isr13);
    setIdtGate(14, (uint32_t)isr14);
    setIdtGate(15, (uint32_t)isr15);
    setIdtGate(16, (uint32_t)isr16);
    setIdtGate(17, (uint32_t)isr17);
    setIdtGate(18, (uint32_t)isr18);
    setIdtGate(19, (uint32_t)isr19);
    setIdtGate(20, (uint32_t)isr20);
    setIdtGate(21, (uint32_t)isr21);
    setIdtGate(22, (uint32_t)isr22);
    setIdtGate(23, (uint32_t)isr23);
    setIdtGate(24, (uint32_t)isr24);
    setIdtGate(25, (uint32_t)isr25);
    setIdtGate(26, (uint32_t)isr26);
    setIdtGate(27, (uint32_t)isr27);
    setIdtGate(28, (uint32_t)isr28);
    setIdtGate(29, (uint32_t)isr29);
    setIdtGate(30, (uint32_t)isr30);
    setIdtGate(31, (uint32_t)isr31);

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

    setIdtGate(32, (uint32_t)irq0);
    setIdtGate(33, (uint32_t)irq1);
    setIdtGate(34, (uint32_t)irq2);
    setIdtGate(35, (uint32_t)irq3);
    setIdtGate(36, (uint32_t)irq4);
    setIdtGate(37, (uint32_t)irq5);
    setIdtGate(38, (uint32_t)irq6);
    setIdtGate(39, (uint32_t)irq7);
    setIdtGate(40, (uint32_t)irq8);
    setIdtGate(41, (uint32_t)irq9);
    setIdtGate(42, (uint32_t)irq10);
    setIdtGate(43, (uint32_t)irq11);
    setIdtGate(44, (uint32_t)irq12);
    setIdtGate(45, (uint32_t)irq13);
    setIdtGate(46, (uint32_t)irq14);
    setIdtGate(47, (uint32_t)irq15);

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

void isrHandler(registers_t *argR)
{
    char s[3];
    kprint("received interrrupt: ");
    itoa(argR->intNumber, s);
    kprint(s);
    kprint("\n");
    kprint(exceptionMessages[argR->intNumber]);
    kprint("\n");
}

void registerInterruptHandler(uint8_t argIntNumber, isr_t argHandler)
{
    interrruptHandlers[argIntNumber] = argHandler;
}

void irqHandler(registers_t *argReg)
{
    /*
     * After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again
     */
     if (argReg->intNumber >= 40)
     {
         portByteOut(SLAVE_PIC_COMMAND, 0x20); /* Slave. */
     }

     portByteOut(MASTER_PIC_COMMAND, 0x20); /* Master. */

     if (interrruptHandlers[argReg->intNumber] != 0)
     {
         isr_t handler = interrruptHandlers[argReg->intNumber];
         handler(argReg);
     }
}

void irqInstall()
{
    /* Enable interrupts. */
    asm volatile("sti");

    initTimer(50);
    initKeyboard();
}
