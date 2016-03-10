SECTION .text

bits 32

; void outb(ushort port, byte value);
global _outb
; void outw(ushort port, ushort value);
global _outw
; void _outdw(ushort port, uint value);
global outdw

; byte inb(ushort port);
global _inb
; ushort inw(ushort port);
global _inw
; uint indw(ushort port);
global _indw

_outb:
mov dx, [esp+4]
mov al, [esp+8]
out dx, al
ret

_outw:
mov dx, [esp+4]
mov ax, [esp+8]
out dx, ax
ret

_outdw:
mov dx, [esp+4]
mov eax, [esp+8]
out dx, eax
ret



_inb:
mov dl, [esp+4]
in al, dx
ret

_inw:
mov dx, [esp+4]
in ax, dx
ret

_indw:
mov edx, [esp+4]
in eax, dx
ret
