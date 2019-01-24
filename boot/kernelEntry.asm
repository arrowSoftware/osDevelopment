;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; File:
;   kernelEntry.asm
;
; Description:
;   This file
;
; Todo:
;   None.
;
; Modification History:
;   Date:       Author:       Description:
;   ============================================================================
;   1/23/2019   T.Gajewski    Initial Release.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
global _start
[bits 32]

_start:
    [extern kernelMain] ; Define calling point. Must have same name as kernel.c 'kernelMain' function
    call kernelMain     ; Calls the C function. The linker will know where it is placed in memory
    jmp $               ; Endless loop.
