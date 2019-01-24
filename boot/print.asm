;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; File:
;   print.asm
;
; Description:
;   This file contains labels to print a string and new line using the BIOS
;   print: prints a string to the screen using the BIOS interrupts.
;       args: 'bx' is the base address of the string to print.
;
;   printNewline: prints a new line to the screen using the BIOS interupts.
;       args: None.
;
; Todo:
;   None.
;
; Modification History:
;   Date:       Author:       Description:
;   ============================================================================
;   1/23/2019   T.Gajewski    Initial Release.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

NEWLINE equ 0x0A         ; The newline byte.
CARRIAGE_RETURN equ 0x0D ; Cariage return.

print:
    pusha ; Push general purpose registers onto the stack.

; Reference: while (string[i] != 0) { print string[i]; i++ }
start:
    mov al, [bx] ; 'bx' is the vase address for the string.
    cmp al, 0    ; Check for null delimeter.
    je done      ; If null is found, finish printing and return.

    ; Use BIOS to print
    mov ah, 0x0E ; Function code to print.
    int 0x10     ; Raise BIOS interrupt.

    ; Increment pointer and do next iteration.
    add bx, 1  ; Increment pointer.
    jmp start  ; Go through next loop interation.

done:
    popa ; pop general purpose registers off the stack.
    ret  ; Return to caller.

printNewline:
    pusha
    mov ah, 0x0E            ; Teletype output.
    mov al, NEWLINE         ; ASCII character for newline.
    int 0x10                ; Raise BIOS interrupt.
    mov al, CARRIAGE_RETURN ; ASCII character for carriage return.
    int 0x10                ; Raise BIOS interrupt.

    popa ; pop general purpose registers off the stack.
    ret  ; Return to caller.
