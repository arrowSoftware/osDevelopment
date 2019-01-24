;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; File:
;   disk.asm
;
; Description:
;   This file contains a label that will read from a disk and store the data
;   in bx(the kernel offset).
;
; Todo:
;   None.
;
; Modification History:
;   Date:       Author:       Description:
;   ============================================================================
;   1/23/2019   T.Gajewski    Initial Release.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Load 'dh' sectors from drive 'dl' into ES:BX
; Our arguments are 'dx', dh is the number of sectors to read, 'dl' is the drive
; to read from.
diskLoad:
    pusha ; Push general purpose registers onto the stack

    ; Reading from the disk requires setting specific values in all registers
    ; so we will overwrite our input parameters from 'dx'.  Let's save it to
    ; the stack for later use.
    push dx

    mov ah, 0x02 ; Store the  int 0x13 'read' function into the upper 8 bits of 'al'.
    mov al, dh   ; Store our argument for number of sectors to read in al, (0x01 .. 0x80)
    mov cl, 0x02 ; Which sector to read (0x01 .. 0x11)
                 ; 0x01 is the boot sector, 0x02 is the first 'available' sector.
    mov ch, 0x00 ; which cylinder to read (0x00 .. 0x3FF, upper 2 bits in 'cl')
                 ; dl <- drive number. Our caller sets it as a parameter and gets it from BIOS
                 ; (0 = floppy, 1 = floppy2, 0x80 = hdd, 0x81 = hdd2)
    mov dh, 0x00 ; Head number (0x0 .. 0xF)

    ; [es:bx] <- pointer to buffer where data will be stored.
    ; caller sets it up for us.
    int 0x13     ; BIOS interrupt.
    jc diskError ; If error (stored in the carry bit)

    pop dx
    cmp al, dh       ; BIOS also sets 'al' to the # of sectors read.
    jne sectorsError ; If sectors are equal jump to error.
    popa             ; pop general purpose registers off the stack.
    ret              ; Return to caller

diskError:
    mov bx, DISK_ERROR ; Move the error message into 'bx' for the argument to print.
    call print         ; Print our error.
    call printNewline  ; Print a new line.
    mov dh, ah         ; ah = error code, dl = disk drive that dropped error.
    call printHex      ; Print error codes in hex.
    jmp diskLoop       ; Jump to main disk loop.

sectorsError:
    mov bx, SECTORS_ERROR ; Move the error message into 'bx' for the argument to print.
    call print            ; Print our error.

diskLoop:
    ; NASM, the dollar operator ($) represents the address of the current line.
    jmp $

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "incorrect number of sectors read", 0
