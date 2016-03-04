;*********************************************
;				boot1.asm
;*********************************************

;*********************************************
;				constants
;*********************************************
OFFSET_LOAD equ 90				; Offset from which bootloader is put in MBR
OFFSET_BOOT equ 0x7c00			; Offset where BIOS has loaded us
OFFSET_JUMP equ 1 + 2			; Offet of JMP command
BOOT2_ENTRY equ 0x1000
BOOT2 equ 0x10000
;*********************************************
;				MBR Real Mode
;*********************************************
org OFFSET_BOOT +  OFFSET_LOAD		; We are loaded by BIOS at 0x7c00
bits 16							; We are in Real mode (16 bit)

;*********************************************
;DO NOT PUT ANY CODE BEFORE gtd.asm OR IT WILL SCREW GDT
;*********************************************


start:	jmp loader

%include "gdt.asm"
%include "io.asm"
%include "fat32.asm"

;call InstallGDT

msg			db	"Welcome to Simple Operating System!", 0 
msg_a20 	db	"A20 Enabled!", 0
msg_boot2	db	"Booting file found!", 0
msg_ok		db	"OK", 0
msg_failed	db	"Failed", 0

;*********************************************
;				main loader routine
;*********************************************
loader:							; Entry point of bootloader
	cli
	xor ax, ax					; Setup segments to insure they are 0. Remember that
	mov ds, ax					; we have ORG 0x7c00. This means all addresses are based
	mov es, ax					; from 0x7c00:0. Because the data segments are within the same code segment, null em
	mov ax, 0x8000				; stack end
	mov ss, ax
	mov sp, 0x8FFF				; stack pointer,begin
	sti
	
	
	;mov	ax, 0x1000			; we are going to read sector to into address 0x1000:0
	;mov	es, ax
	;xor	bx, bx
	;call Read
	
SetTextMode:
	mov ah, 0x00
	mov al, 0x03
	int 0x10
	
PrintWelcome:

	mov si, msg 
	call Print
	call PrintNewLine

Booting:
	;call GetHDDInfo
	;cmp dl, 0
	;jne Failed

	;and cl, 0x3f
	
	;cli
	;hlt

	;Set drive type reported from bios
	;mov dl ,bl

	;SCREW FAT32, First after is boot2
	;Load it, limit is cluster size (4KB)
	;Load in 36Kb
	mov ax, BOOT2_ENTRY
	mov es, ax
	xor bx, bx

	;mov ah, 0
	;int 0x16

	mov al, 2 * FAT32_CLUSTER_SIZE / SECTOR_SIZE
	mov ch, 4
	mov cl, 11
	mov dh, 2
	call ReadFromHDD
	
	
	;FILE IS IN MEMORY, BITCHES
	mov si, msg_boot2
	call Print
	call PrintNewLine

	call EnableA20
	call InstallGDT
	
	
	call EnterProtectedMode

Failed:
	mov si, msg_failed 
	call Print
	cli
	hlt

EnableA20:
	pusha
	mov ax, 0x2401
	int 0x15
	
	jc Failed
	
	mov si, msg_a20  
	call Print
	
	popa
	ret
	

EnterProtectedMode:
	cli
	
	mov eax, cr0
	or	eax, 1
	mov	cr0, eax
	

	jmp GCD:ProtectedMode


bits 32

ProtectedMode:


	mov ax, GDD

	mov ds, ax
	mov	ss, ax
	mov es,	ax

	mov fs, ax
	mov gs, ax
	
	mov esp, 0xFFFF					; stack pointer from
	

	;cld
	;mov	edi, 0xA0000 ;[esp + 6]	; get the 2nd parameter off the stack
	;mov	cx,	2000
	;mov	ah, 14 ;	[esp + 4]		;  get the 1st parameter off the stack
	;mov	al, ' '
	;rep	stosw

	;mov	al, 0x0f
	;mov	dx, 0x03D4
	;out	dx, al

	;mov	al, 10  
	;mov	dx, 0x03D5
	;out	dx, al

	jmp GCD:BOOT2

	
	times 510 - OFFSET_LOAD - ($-$$) db 0		; Clear the remaining bytes up to 510 - offet
	
	dw 0xAA55					; Boot Signature (511 & 512 byte)
