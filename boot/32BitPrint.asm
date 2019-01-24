;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; File:
;   32BitPrint.asm
;
; Description:
;   This file contains a label that will print a string in 32 bit protected
;   mode.
;
; Todo:
;   None.
;
; Modification History:
;   Date:       Author:       Description:
;   ============================================================================
;   1/23/2019   T.Gajewski    Initial Release.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[bits 32] ; Using 32 bit protected mode

VIDEO_MEMORY equ 0xB8000 ; The address of video mempry.
WHITE_ON_BLACK equ 0x0F  ; The color byte for each character.

printStringPm:
    pusha                 ; Push general purpose registers onto the stack
    mov edx, VIDEO_MEMORY ; Store video memory in edx for later.

; Input: ebx, ebx being tbe base address of the string to print.
printStringPmLoop:
    ; Video memory takes 2 bytes, the character to print and the color.
    mov al, [ebx]          ; The address of our character.
    mov ah, WHITE_ON_BLACK ; Store color.

    cmp al, 0              ; Check for end of string.
    je printStringPmDone   ; If end of string found, jump to done.

    mov [edx], ax ; Store character + attribute in video memory.
    add ebx, 1    ; Next character.
    add edx, 2    ; Next video memory position.

    jmp printStringPmLoop ; Start loop over again until end of string found.

printStringPmDone:
    popa ; pop general purpose registers off the stack.
    ret  ; Return to caller.
