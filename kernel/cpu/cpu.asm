;http://www.osdever.net/bkerndev/Docs/isrs.htm

SECTION .text

bits 32

extern _TestMethod

global _load_idt

idt:
	dw 8 * 256 - 1
	dd 0x1000000
	
_load_idt:
	;jmp _TestMethod
	lidt [idt]
	ret

GDT_CODE equ 0x08
GDT_DATA equ 0x10

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, GDT_DATA   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, _TestMethod
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
