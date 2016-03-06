SECTION .text

bits 32

global _load_idt

;extern _idtp

idt:
	dw 8*256-1
	dd 0x110000
_load_idt:
	lidt [idt]
	ret
