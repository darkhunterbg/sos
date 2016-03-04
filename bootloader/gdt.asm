;*********************************************
;				gdt.asm
;*********************************************

%ifndef __gdt_asm__
%define __gdt_asm__


;*********************************************
;			Global Descriptor Table
;*********************************************

; access  :
;Bit 0 (Bit 40 in GDT): Access bit (Used with Virtual Memory). Because we don't use virtual memory (Yet, anyway), we will ignore it. Hence, it is 0
;Bit 1 (Bit 41 in GDT): is the readable/writable bit. Its set (for code selector), so we can read and execute data in the segment (From 0x0 through 0xFFFF) as code
;Bit 2 (Bit 42 in GDT): is the "expansion direction" bit. We will look more at this later. For now, ignore it.
;Bit 3 (Bit 43 in GDT): tells the processor this is a code or data descriptor. (It is set, so we have a code descriptor)
;Bit 4 (Bit 44 in GDT): Represents this as a "system" or "code/data" descriptor. This is a code selector, so the bit is set to 1.
;Bits 5-6 (Bits 45-46 in GDT): is the privilege level (i.e., Ring 0 or Ring 3). We are in ring 0, so both bits are 0.
;Bit 7 (Bit 47 in GDT): Used to indicate the segment is in memory (Used with virtual memory). Set to zero for now, since we are not using virtual memory yet

; granuality :
;Bit 0-3 (Bits 48-51 in GDT): Represents bits 16-19 of the segment limit. So, lessee... 1111b is equal to 0xf. Remember that, in the first two bytes if this descriptor, we set 0xffff as the first 15 bites. Grouping the low and high bits, it means we can access up to 0xFFFFF. Cool? It gets better... By enabling the 20th address line, we can access up to 4 GB of memory using this descriptor. We will look closer at this later...
;Bit 4 (Bit 52 in GDT): Reserved for our OS's use--we could do whatever we want here. Its set to 0.
;Bit 5 (Bit 53 in GDT): Reserved for something. Future options, maybe? Who knows. Set to 0.
;Bit 6 (Bit 54 in GDT): is the segment type (16 or 32 bit). Lessee.... we want 32 bits, don't we? After all-we are building a 32 bit OS! So, yeah--Set to 1.
;Bit 7 (Bit 55 in GDT): Granularity. By setting to 1, each segment will be bounded by 4KB.


; based on offset 90
bits	16


OFFSET_LOW equ 0x005A				; 0x5A = 90
OFFSET_MIDDLE equ 0x0000

OFFSET_TOTAL equ  OFFSET_LOAD 

OFFSET_GDT equ 3*8				; Offset from GDT - 3 * 8 bytes

GCD equ gdt_code - gdt_start 
GDD equ gdt_data - gdt_start 


InstallGDT:
	cli
	
	lgdt [toc]
	
	sti
	ret
	
InstallIDT:
	cli
	
	lidt [idt]
	
	sti
	ret

gdt_start:
; null descriptor 0x00
gdt_null:
	dd 0
	dd 0

; code descriptor 0x08
gdt_code:
	dw 0xFFFF					; limit low
	dw 0						; base low
	db 0						; base middle
	db 10011010b				; access
	db 11001111b				; granualarity
	db 0						; base high
	
; data descriptor 0x10
gdt_data:
	dw 0xFFFF					; limit low
	dw 0						; base low
	db 0						; base middle
	db 10010010b				; access
	db 11001111b				; granualarity
	db 0						; base high


end_of_gdt:
toc:
	dw end_of_gdt - gdt_start - 1; limit(Size of GDT)
	dd gdt_start				; base of GDT

isr:
	dw 0

idt_start:
idt_interrupt_gate:
	dw isr						; interrupt service routine low
	dw GCD						; segment (must be the same as isr)
	db 0						; zero
	db 00001110b				; access
	dw 0						; interrupt service routine high

idt_task_gate:
	dw 0						; interrupt service routine low
	dw GCD						; segment (must be the same as isr)
	db 0						; zero
	db 10010101b				; access
	dw 0						; interrupt service routine high
idt_end:
idt:
	dw 2048
	;dw idt_end - idt_start - 1; limit(Size of IDT)
	dd idt_start				; base of IDT
%endif
