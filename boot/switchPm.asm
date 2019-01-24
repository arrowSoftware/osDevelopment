;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; File:
;   switchPm.asm
;
; Description:
;   This file contains a label that will switch to 32 bit protected mode.
;
; Todo:
;   None.
;
; Modification History:
;   Date:       Author:       Description:
;   ============================================================================
;   1/23/2019   T.Gajewski    Initial Release.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; The CR0 32-bit register has 6 bits that are of interest to us. The low 5 bits of
; the CR0 register, and the highest bit. Here is a representation of CR0:
;   CR0: |PG|----RESERVED----|NE|ET|TS|EM|MP|PE|
;   PE: Bit 0. The Protected Environment flag. This flag puts the system into
;              protected mode when set.

[bits 16]
switchToPm:
    cli                  ; step 1. Disable interrupts.
    lgdt [gdtDescriptor] ; step 2. Load the GDT descriptor.
    mov eax, cr0         ; Store control register to update next.
    or eax, 0x1          ; step 3. Set 32 bit mode in cr0.
    mov cr0, eax         ; Write update back to control register.
    jmp CODE_SEG:initPm  ; step 4. Far jump by usng a different segment.

[bits 32]
initPm: ; Start using 32 bit instructions.
    mov ax, DATA_SEG ; step 5. Update the segment registers.
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; step 6. Update the stack right at the top of the free space, Todo: why 0x90000
    mov esp, ebp

    call BEGIN_PM   ; step 7. Call a well known label with useful code.
