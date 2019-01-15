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
    mov ah, 0x0E ; Teletype output.
    mov al, 0x0A ; ASCII character for newline.
    int 0x10     ; Raise BIOS interrupt.
    mov al, 0x0D ; ASCII character for carriage return.
    int 0x10     ; Raise BIOS interrupt.

    popa ; pop general purpose registers off the stack.
    ret  ; Return to caller.
