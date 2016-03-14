;http://www.osdever.net/bkerndev/Docs/isrs.htm

SECTION .text

bits 32

extern __fault
extern __trap
extern __abort

extern __irq

global _load_idt
global isr_fault_stub


idt:
	dw 8 * 48 - 1
	dd 0x1000000
	
_load_idt:
	lidt [idt]
	ret

GDT_CODE equ 0x08
GDT_DATA equ 0x10

global _isr0
global _isr1
global _isr2
global _isr3
global _isr4
global _isr5
global _isr6
global _isr7
global _isr8
global _isr9
global _isr10
global _isr11
global _isr12
global _isr13
global _isr14
global _isr15
global _isr16
global _isr17
global _isr18
global _isr19
global _isr20
global _isr21
global _isr22
global _isr23
global _isr24
global _isr25
global _isr26
global _isr27
global _isr28
global _isr29
global _isr30
global _isr31

global _irq

global _irq0
global _irq1
global _irq2
global _irq3
global _irq4
global _irq5
global _irq6
global _irq7
global _irq8
global _irq9
global _irq10
global _irq11
global _irq12
global _irq13
global _irq14
global _irq15


_irq:
	cli
	hlt
	iret

_isr0:
	cli
	push byte 0
	push byte 0
	jmp isr_fault_stub
	
_isr1:
	cli
	push byte 0
	push byte 1
	jmp isr_trap_stub
	
_isr2:
	cli
	push byte 0
	push byte 2
	jmp isr_fault_stub
	
_isr3:
	cli
	push byte 0
	push byte 3
	jmp isr_trap_stub
	
	_isr4:
	cli
	push byte 0
	push byte 4
	jmp isr_trap_stub

_isr5:
	cli
	push byte 0
	push byte 5
	jmp isr_fault_stub

_isr6:
	cli
	push byte 0
	push byte 6
	jmp isr_fault_stub
	
_isr7:
	cli
	push byte 0
	push byte 7
	jmp isr_fault_stub
	
_isr8:
	cli
	push byte 8
	jmp isr_abort_stub
	
_isr9:
	cli
	push byte 0
	push byte 9
	jmp isr_fault_stub
	
_isr10:
	cli
	push byte 10
	jmp isr_fault_stub
	
_isr11:
	cli
	push byte 11
	jmp isr_fault_stub
	
_isr12:
	cli
	push byte 12
	jmp isr_fault_stub
	
_isr13:
	cli
	push byte 13
	jmp isr_fault_stub
	
_isr14:
	cli
	push byte 14
	jmp isr_fault_stub
	
_isr15:
	cli
	push byte 0
	push byte 15
	jmp isr_fault_stub
	
_isr16:
	cli
	push byte 0
	push byte 16
	jmp isr_fault_stub
	
_isr17:
	cli
	push byte 17
	jmp isr_fault_stub
	
_isr18:
	cli
	push byte 0
	push byte 18
	jmp isr_abort_stub
	
_isr19:
	cli
	push byte 0
	push byte 19
	jmp isr_fault_stub
	
_isr20:
	cli
	push byte 0
	push byte 20
	jmp isr_fault_stub
	
_isr21:
	cli
	push byte 0
	push byte 21
	jmp isr_fault_stub
	
_isr22:
	cli
	push byte 0
	push byte 22
	jmp isr_fault_stub
	
_isr23:
	cli
	push byte 0
	push byte 23
	jmp isr_fault_stub
	
_isr24:
	cli
	push byte 0
	push byte 24
	jmp isr_fault_stub
	
_isr25:
	cli
	push byte 0
	push byte 25
	jmp isr_fault_stub
	
_isr26:
	cli
	push byte 0
	push byte 26
	jmp isr_fault_stub
	
_isr27:
	cli
	push byte 0
	push byte 27
	jmp isr_fault_stub
	
_isr28:
	cli
	push byte 0
	push byte 28
	jmp isr_fault_stub
	
_isr29:
	cli
	push byte 0
	push byte 29
	jmp isr_fault_stub
	
_isr30:
	cli
	push byte 30
	jmp isr_fault_stub
	
_isr31:
	cli
	push byte 0
	push byte 31
	jmp isr_fault_stub


; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_fault_stub:
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
    mov eax, __fault
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!


isr_trap_stub:
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
    mov eax, __trap
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
	
	
isr_abort_stub:
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
    mov eax, __abort
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!


irq_stub:
	mov eax, __irq
	call eax
	add esp, 4
	
	;mov dx, 0x20
	;mov al, 0x20
	;out dx, al
	
	iret
	
_irq0:
	push byte 0
	jmp irq_stub
	
_irq1:
	push byte 1
	jmp irq_stub
	
_irq2:
	push byte 2
	jmp irq_stub
	
_irq3:
	push byte 3
	jmp irq_stub
	
_irq4:

	push byte 4
	jmp irq_stub
	
_irq5:
	push byte 5
	jmp irq_stub
	
_irq6:
	push byte 6
	jmp irq_stub
	
_irq7:
	push byte 7
	jmp irq_stub
	
_irq8:
	push byte 8
	jmp irq_stub
	
_irq9:
	push byte 9
	jmp irq_stub
	
_irq10:
	cli
	push byte 10
	jmp irq_stub
	
_irq11:
	push byte 11
	jmp irq_stub
	
_irq12:
	push byte 12
	jmp irq_stub
	
_irq13:
	push byte 13
	jmp irq_stub
	
_irq14:
	push byte 14
	jmp irq_stub
	
_irq15:
	push byte 15
	jmp irq_stub

