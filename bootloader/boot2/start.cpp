//DO NOT INCLUDE ANYTHING BEFORE START
//OR I'LL HUNT YOU DOWN

#include "memory.h"
#include "vga.h"
#include "disk.h"
#include "io.h"

void boot2();
void PrintDiskInfo(DiskService&, VgaService&);
void ShowSuccess(const char* msg, VgaService& vgaService);
void ShowFailed(const char* msg, VgaService& vgaService);

int start()
{
    boot2();
    return 0;
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

    vgaService.SetCursorPos(15, 10);
    vgaService.SetCursorColor(0x0F);
    vgaService.Print("I am preparing to load... Hold on, please... :)");

    vgaService.SetCursorPos(0, 15);
    if(diskService.DetectPrimaryDisk())
	ShowSuccess("Primary hard drive detected!\n", vgaService);
    else
	{
	    ShowFailed("Primary hard drive not found!", vgaService);
		asm("hlt"); 
	}
    byte a = 0x00;
    byte b = 0x10;
    while(true)
	{
	    uint x = 0;
	    vgaService.SetCursorColor(b);
	    byte c = a;
	    a = b;
	    b = c;
	    for(uint i = 0; i < VgaService::COLUMNS; ++i)
		{
		    for(uint j = 0; j < 40000; ++j)
			{
			    vgaService.SetCursorPos(x, 22);
			}
		    vgaService.Print(' ');
		    ++x;
		}
	}

    asm("hlt");
}

void ShowSuccess(const char* msg, VgaService& vgaService)
{
    // vgaService.SetCursorPos(0, 20);
    vgaService.SetCursorColor(0x02);
    vgaService.Print(msg);
}
void ShowFailed(const char* msg, VgaService& vgaService)
{
    // vgaService.SetCursorPos(0, 20);
    vgaService.SetCursorColor(0x04);
    vgaService.Print(msg);
}

void PrintDiskInfo(DiskService& diskService, VgaService& vgaService)
{
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
}
