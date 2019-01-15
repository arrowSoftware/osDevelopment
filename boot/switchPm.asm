[bits 16]

; PM = Protected Mode
switchToPm:
    cli                  ; step 1. Disable interrupts
    lgdt [gdtDescriptor] ; step 2. Load the GDT descriptor, TODO: what is lgdt
    mov eax, cr0         ; TODO
    or eax, 0x1          ; step 3. Set 32 bit mode in cr0
    mov cr0, eax         ; TODO
    jmp CODE_SEG:initPm  ; step 4. Far jump by usng a different segment.

[bits 32]
initPm: ; Start using 32 bit instructions.
    mov ax, DATA_SEG ; step 5. Update the segment registers.
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x9000 ; step 6. Update the stack right at the top of the free space
    mov esp, ebp

    call BEGIN_PM   ; step 7. Call a well known label with useful code.
