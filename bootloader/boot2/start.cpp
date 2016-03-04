//DO NOT INCLUDE ANYTHING BEFORE START
//OR I'LL HUNT YOU DOWN

void boot2();

int start()
{
    boot2();
    return 0;
}

#include "memory.h"
#include "vga.h"
#include "disk.h"
#include "io.h"

void PrintDiskInfo(DiskService&, VgaService&);

inline void* operator new(uint, void* p) throw()
{
    return p;
}
inline void* operator new[](uint, void* p) throw()
{
    return p;
}
inline void operator delete(void*, void*) throw()
{
}
inline void operator delete[](void*, void*) throw()
{
}

void boot2()
{
    MemoryService memoryService;
    DiskService diskService;
    VgaService vgaService;

    vgaService.ClearScreen(0x00);

    vgaService.SetCursorColor(0x07);
    vgaService.SetCursorPos(16, 3);

    vgaService.Print("+-----------------------------------------+");
    vgaService.SetCursorPos(16, 4);
    vgaService.Print("|    SOS 32 Bit C++ Kernel Executing!     |");
    vgaService.SetCursorPos(16, 5);
    vgaService.Print("+-----------------------------------------+");

    vgaService.SetCursorPos(16, 16);
    vgaService.SetCursorColor(0x0F);
    vgaService.Print("I am preparing to load... Hold on, please... :)");

    const FAT32BootRecord& bootRecord = diskService.GetBootRecord();
    const FAT32ExtendedBootRecord& extendedRecord = diskService.GetExtendedBootRecord();

    vgaService.SetCursorPos(0, 10);
    vgaService.SetCursorColor(0x0B);
    vgaService.Print("OEM: ");
    vgaService.Print(bootRecord.oem);
    vgaService.Print(" Label: ");
    vgaService.Print(extendedRecord.volumeLabel, 11);
    vgaService.Print(" Identifier: ");
    vgaService.Print(extendedRecord.identifier, 8);


	outb(0x1F6,0xA0);
	outb(0x1F2,0x0);
	outb(0x1F3,0x0);
	outb(0x1F4,0x0);
	outb(0x1F5,0x0);
	outb(0x1F7,0xEC);
	byte status = inb(0x1F7);
	vgaService.Print(static_cast<uint>(status & 0x08)); 
   // PrintDiskInfo(diskService, vgaService);

    vgaService.SetCursorColor(0x07);
    uint x = 0;
    for(uint i = 0; i < 320; ++i)
	{
	    for(uint j = 0; j < 100000; ++j)
		{
		    vgaService.SetCursorPos(x, 20);
		}
	    vgaService.Print('=');
	    ++x;
	}

   asm("hlt");
}

void PrintDiskInfo(DiskService& diskService, VgaService& vgaService)
{
   // const FAT32ExtendedBootRecord& extendedRecord = diskService.GetExtendedBootRecord();

    vgaService.SetCursorPos(0, 10);
    vgaService.SetCursorColor(0x0B);
    vgaService.Print("OEM: ");
}
