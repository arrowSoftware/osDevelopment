[bits 32] ; Using 32 bit protected mode

; Define contants
VIDEO_MEMORY equ 0xB8000
WHITE_ON_BLACK equ 0x0F ; The color byte for each character.

printStringPm:
    pusha  ; Push general purpose registers onto the stack
    mov edx, VIDEO_MEMORY

printStringPmLoop:
    mov al, [ebx] ; The address of our character.
    mov ah, WHITE_ON_BLACK

    cmp al, 0 ; Check for end of string.
    je printStringPmDone

    mov [edx], ax ; Store character + attribute in video memory.
    add ebx, 1    ; Next character.
    add edx, 2    ; Next video mempry position.

    jmp printStringPmLoop

printStringPmDone:
    popa ; pop general purpose registers off the stack.
    ret  ; Return to caller.
