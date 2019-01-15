[org 0x7C00] ; TODO
KERNEL_OFFSET equ 0x1000 ; The same that was used when linking the kernel

    mov [BOOT_DRIVE], dl ; The BIOS sets us the boot drive in 'dl' on boot
    mov bp, 0x9000 ; Set the stack safetly away from us.
    mov sp, bp     ; Update stack pointer.

    mov bx, MSG_REAL_MODE
    call print
    call printNewline

    call loadKernel ; Read the kernel from the disk
    call switchToPm ; disable interrupts, load GDT,  etc. Finally jumps to 'BEGIN_PM'
    jmp $           ; Never executed.

%include "boot/print.asm"
%include "boot/printHex.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/32BitPrint.asm"
%include "boot/switchPm.asm"

[bits 16]
loadKernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call printNewline

    mov bx, KERNEL_OFFSET ; Read from the disk and store in 0x1000
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call diskLoad
    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call printStringPm
    call KERNEL_OFFSET ; Give control to the kernel
    jmp $

BOOT_DRIVE db 0 ; It is a good idea to store it in memory because 'dl' may get overwritten
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

; NASM, the dollar operator ($) represents the address of the current line.
; $$ represents the address of the first instruction (Should be 0x7C00). So,
; $­$$ returns the number of bytes from the current line to the start
; (In this case, the size of the program).
; Repeat the db instaruction x amount of times to reach 512 bytes. 510 becuase
; the last two bytes must be 0xAA55
times 510-($-$$) db 0 ; We have to be 512 bytes, clear the rest of the bytes
                      ; with 0

; The BIOS INT 0x19 searches for a bootable disk. How does it know
; if the disk is bootable? The boot signiture. If the 511 byte is 0xAA and the
; 512 byte is 0x55, INT 0x19 will load and execute the bootloader. Because the
; boot signiture must be the last two bytes in the bootsector, We use the times
; keyword to calculate the size different to fill in up to the 510th byte,
; rather then the 512th byte.
dw 0xAA55 ; Boot signature.
