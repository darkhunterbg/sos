;*********************************************
;				fat32.asm
;*********************************************

%ifndef __fat32_asm__
%define __fat32_asm__

FAT32_SIGNATURE equ 0x29
FAT32_SIGNATURE_OFFSET equ 66
FAT32_CLUSTER_NUMBER_ROOT_OFFSET equ 44

FAT32_CLUSTER_SIZE equ 4* 1024

;al = 0x28 or 0x29
Fat32GetSignature:
	mov al,[OFFSET_BOOT + FAT32_SIGNATURE_OFFSET]

;eax = number of clusters in root
Fat32GetRootClusterCount:
	mov eax,[OFFSET_BOOT + FAT32_CLUSTER_NUMBER_ROOT_OFFSET]


%endif
