/*******************************************************************************
 * File:
 *  isr.h
 *
 * Description:
 *  This file contains the function to install interrupt service routines.
 *
 * Members:
 *  isr<0...31>();
 *  irq<0...15>();
 *  isrInstall();
 *  isrHandler(registers_t *argR);
 *  irqInstall();
 *  registerInterruptHandler(uint8_t argIntNumber, isr_t argHandler);
 *
 * Todo:
 *
 *
 * Modification History:
 *  Date         Who         Description
 *  ============================================================================
 *  01/17/19    T.Gajewski   Initial version.
 ******************************************************************************/

#ifndef _ISR_H_
#define _ISR_H_

#include "types.h"

/* ISRs reserved for CPU exceptions */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/* IRQ definitions */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/*
 * Master PIC
 * IRQ 0 – system timer (cannot be changed)
 * IRQ 1 – keyboard controller (cannot be changed)
 * IRQ 2 – cascaded signals from IRQs 8–15 (any devices configured to use IRQ 2
 *         will actually be using IRQ 9)
 * IRQ 3 – serial port controller for serial port 2
 *         (shared with serial port 4, if present)
 * IRQ 4 – serial port controller for serial port 1
 *         (shared with serial port 3, if present)
 * IRQ 5 – parallel port 2 and 3  or  sound card
 * IRQ 6 – floppy disk controller
 * IRQ 7 – parallel port 1. It is used for printers or for any parallel port if
 *         a printer is not present. It can also be potentially be shared with a
 *         secondary sound card with careful management of the port.
 * Slave PIC
 * IRQ 8 – real-time clock (RTC)
 * IRQ 9 – Advanced Configuration and Power Interface (ACPI) system control
 *         interrupt on Intel chipsets.[1] Other chipset manufacturers might use
 *         another interrupt for this purpose, or make it available for the use
 *         of peripherals (any devices configured to use IRQ 2 will actually be
 *         using IRQ 9)
 * IRQ 10 – The Interrupt is left open for the use of peripherals
 *          (open interrupt/available, SCSI or NIC)
 * IRQ 11 – The Interrupt is left open for the use of peripherals
 *          (open interrupt/available, SCSI or NIC)
 * IRQ 12 – mouse on PS/2 connector
 * IRQ 13 – CPU co-processor  or  integrated floating point unit  or
 *          inter-processor interrupt (use depends on OS)
 * IRQ 14 – primary ATA channel (ATA interface usually serves hard disk
 *          drives and CD drives)
 * IRQ 15 – secondary ATA channel
 */
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

/*
* It matches exactly the pushes on interrupt.asm. From the bottom:
* - Pushed by the processor automatically
* - `push byte`s on the isr-specific code: error code, then int number
* - All the registers by pusha
* - `push eax` whose lower 16-bits contain DS
*/
typedef struct {
  uint32_t ds; /* Data segment selector */
  uint32_t edi, esi, ebp, useless, ebx, edx, ecx, eax; /* Pushed by pusha. */
  uint32_t intNumber, errorCode; /* Interrupt number and error code (if applicable) */
  uint32_t eip, cs, eflags, esp, ss; /* Pushed by the processor automatically */
} registers_t;

void isrInstall();
void isrHandler(registers_t *argR);
void irqInstall();

typedef void (*isr_t)(registers_t*);
void registerInterruptHandler(uint8_t argIntNumber, isr_t argHandler);

#endif /* _ISR_H_ */
