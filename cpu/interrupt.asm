[extern isrHandler] ; defined in isr.c
[extern irqHandler]

; common isr code
isrCommonStub:
    ; Step 1. save CPU state.
    pusha ; pushes edi,esi,ebp,esp,ebx,edx,ecx,eax.
    mov ax, ds ; Lower 16 bited of eax.
    push eax   ; Save the data segment register.
    mov ax, 0x10 ; Kernel data segment descriptor.
    mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	push esp ; registers_t *r

    ; Step 2. Call C handler
    cld ; C code following the sysV ABI requires DF to be clear on function entry
    call isrHandler

    ; Step 3. Restore state.
    pop eax
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8  ; Cleans up the pushed error code and pushed ISR number
    iret ; Pops 5 things at once: CS, EIP, EFLAGS, SS, ESP

; Common IRQ code. Identical to ISR code except for the 'call'
; and the 'pop ebx'
irqCommonStub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    cld
    call irqHandler ; Different than the ISR code
    pop ebx         ; Different than the ISR code
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
    add esp, 8
    iret

; We don't get information about which interrupt was caller
; when the handler is run, so we will need to have a different handler
; for every interrupt.
; Furthermore, some interrupts push an error code onto the stack but others
; don't, so we will push a dummy error code for those which don't, so that
; we have a consistent stack for all of them.

; First make the ISRs global
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; IRQs
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15


; 0: Divide By Zero Exception
isr0:

    push byte 0
    push byte 0
    jmp isrCommonStub

; 1: Debug Exception
isr1:

    push byte 0
    push byte 1
    jmp isrCommonStub

; 2: Non Maskable Interrupt Exception
isr2:

    push byte 0
    push byte 2
    jmp isrCommonStub

; 3: Int 3 Exception
isr3:

    push byte 0
    push byte 3
    jmp isrCommonStub

; 4: INTO Exception
isr4:

    push byte 0
    push byte 4
    jmp isrCommonStub

; 5: Out of Bounds Exception
isr5:

    push byte 0
    push byte 5
    jmp isrCommonStub

; 6: Invalid Opcode Exception
isr6:

    push byte 0
    push byte 6
    jmp isrCommonStub

; 7: Coprocessor Not Available Exception
isr7:

    push byte 0
    push byte 7
    jmp isrCommonStub

; 8: Double Fault Exception (With Error Code!)
isr8:

    push byte 8
    jmp isrCommonStub

; 9: Coprocessor Segment Overrun Exception
isr9:

    push byte 0
    push byte 9
    jmp isrCommonStub

; 10: Bad TSS Exception (With Error Code!)
isr10:

    push byte 10
    jmp isrCommonStub

; 11: Segment Not Present Exception (With Error Code!)
isr11:

    push byte 11
    jmp isrCommonStub

; 12: Stack Fault Exception (With Error Code!)
isr12:

    push byte 12
    jmp isrCommonStub

; 13: General Protection Fault Exception (With Error Code!)
isr13:

    push byte 13
    jmp isrCommonStub

; 14: Page Fault Exception (With Error Code!)
isr14:

    push byte 14
    jmp isrCommonStub

; 15: Reserved Exception
isr15:

    push byte 0
    push byte 15
    jmp isrCommonStub

; 16: Floating Point Exception
isr16:

    push byte 0
    push byte 16
    jmp isrCommonStub

; 17: Alignment Check Exception
isr17:

    push byte 0
    push byte 17
    jmp isrCommonStub

; 18: Machine Check Exception
isr18:

    push byte 0
    push byte 18
    jmp isrCommonStub

; 19: Reserved
isr19:

    push byte 0
    push byte 19
    jmp isrCommonStub

; 20: Reserved
isr20:

    push byte 0
    push byte 20
    jmp isrCommonStub

; 21: Reserved
isr21:

    push byte 0
    push byte 21
    jmp isrCommonStub

; 22: Reserved
isr22:

    push byte 0
    push byte 22
    jmp isrCommonStub

; 23: Reserved
isr23:

    push byte 0
    push byte 23
    jmp isrCommonStub

; 24: Reserved
isr24:

    push byte 0
    push byte 24
    jmp isrCommonStub

; 25: Reserved
isr25:

    push byte 0
    push byte 25
    jmp isrCommonStub

; 26: Reserved
isr26:

    push byte 0
    push byte 26
    jmp isrCommonStub

; 27: Reserved
isr27:

    push byte 0
    push byte 27
    jmp isrCommonStub

; 28: Reserved
isr28:

    push byte 0
    push byte 28
    jmp isrCommonStub

; 29: Reserved
isr29:

    push byte 0
    push byte 29
    jmp isrCommonStub

; 30: Reserved
isr30:

    push byte 0
    push byte 30
    jmp isrCommonStub

; 31: Reserved
isr31:

    push byte 0
    push byte 31
    jmp isrCommonStub


; IRQ handlers
irq0:

	push byte 0
	push byte 32
	jmp irqCommonStub

irq1:

	push byte 1
	push byte 33
	jmp irqCommonStub

irq2:

	push byte 2
	push byte 34
	jmp irqCommonStub

irq3:

	push byte 3
	push byte 35
	jmp irqCommonStub

irq4:

	push byte 4
	push byte 36
	jmp irqCommonStub

irq5:

	push byte 5
	push byte 37
	jmp irqCommonStub

irq6:

	push byte 6
	push byte 38
	jmp irqCommonStub

irq7:

	push byte 7
	push byte 39
	jmp irqCommonStub

irq8:

	push byte 8
	push byte 40
	jmp irqCommonStub

irq9:

	push byte 9
	push byte 41
	jmp irqCommonStub

irq10:

	push byte 10
	push byte 42
	jmp irqCommonStub

irq11:

	push byte 11
	push byte 43
	jmp irqCommonStub

irq12:

	push byte 12
	push byte 44
	jmp irqCommonStub

irq13:

	push byte 13
	push byte 45
	jmp irqCommonStub

irq14:
	
	push byte 14
	push byte 46
	jmp irqCommonStub

irq15:

	push byte 15
	push byte 47
	jmp irqCommonStub
