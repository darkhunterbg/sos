;*********************************************
;				io.asm
;*********************************************

%ifndef __io_asm__
%define __io_asm__

;***************************************
;INT 0x10 - VIDEO TELETYPE OUTPUT

;AH = 0x0E
;AL = Character to write
;BH - Page Number (Should be 0)
;BL = Foreground color (Graphics Modes Only)
;***************************************

Print:
	pusha
	mov	ah,	0eh	
	jmp PrintChar
PrintChar:
	lodsb					; load next byte from string from SI to AL
	or	al, al				; Does AL=0?
	jz	PrintDone			; Yep, null terminator found-bail out
	int	10h					; Nope-Print the character
	jmp	PrintChar				; Repeat until null terminator found
PrintDone:
	popa
	ret						; we are done, so return

PrintNewLine:
	pusha
	mov ah, 03h				; Get current cursor pos
	mov bh, 0
	int 10h
	
	mov al, dh				; Get current row
	add al, 1				; increment by 1
	
	mov dh, al				; set incremented row
	mov dl, 0
	mov ah, 02h
	int 10h
	
	popa
	ret



;***************************************
;INT 0x13/AH=0x02 - DISK : READ SECTOR(S) INTO MEMORY
;AH = 0x02
;AL = Number of sectors to read
;CH = Low eight bits of cylinder number
;CL = Sector Number (Bits 0-5). Bits 6-7 are for hard disks only
;DH = Head Number
;DL = Drive Number (Bit 7 set for hard disks)
;ES:BX = Buffer to read sectors to

;Returns:
;AH = Status Code
;AL = Number of sectors read
;CF = set if failure, cleared is successfull
;***************************************

SECTOR_SIZE equ 512						; Size of sector
DRIVE_FLOPPY equ 0x00
DRIVE_HDD equ 0x80

;AL = SectorCount; CH = Cylinder Number, CH = Sector Number; DH = Head Number
ReadFromHDD:
	mov ah, 0x02
	;mov al, 1							; Read Sector Count
	;mov ch, 0 + 0						; Cylinder Number
	;mov cl, 1 + 1						; Sector Number
	;mov dh, 0							; Head Number
	mov dl, DRIVE_HDD + 0				; Read From HDD
	int 0x13
	
	jc ReadFromHDD							; OnError
	
	ret
	

;OUT:
;AH = return code; DL = number of HDD; DH = heads -1; CX = cylinders -1 ; CL AND 0x3f = Sectors per Track; BL = drive type; 
GetHDDInfo:
	xor ax, ax
	mov es, ax
	mov di, ax
	mov ah, 0x08
	mov dl, DRIVE_HDD 
	int 0x13
	
	jc GetHDDInfo
	
	ret

%endif
