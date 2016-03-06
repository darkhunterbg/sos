SECTION .text

bits 32

global _load_idt

idt:
	dw 8 * 256 - 1
	dd 0x1000000
	
_load_idt:
	lidt [idt]
	ret
