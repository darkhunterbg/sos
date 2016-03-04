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
void ShowSuccess(const char* msg, VgaService& vgaService);
void ShowFailed(const char* msg, VgaService& vgaService);

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

    /*
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
	*/


    if(diskService.DetectPrimaryDisk())
	ShowSuccess("Primary hard drive detected!", vgaService);
    else
	ShowFailed("Primary hard drive not found!", vgaService);

    vgaService.SetCursorColor(0x07);
    uint x = 0;

    for(uint i = 0; i < VgaService::COLUMNS; ++i)
	{
	    for(uint j = 0; j < 200000; ++j)
		{
		    vgaService.SetCursorPos(x, 22);
		}
	    vgaService.Print('=');
	    ++x;
	}

    asm("hlt");
}

void ShowSuccess(const char* msg, VgaService& vgaService)
{
	return;
    vgaService.SetCursorPos(0, 20);
    vgaService.SetCursorColor(0x07);
    vgaService.Print(msg);
}
void ShowFailed(const char* msg, VgaService& vgaService)
{
	return;
    vgaService.SetCursorPos(0, 20);
    vgaService.SetCursorColor(0x07);
    vgaService.Print(msg);
}

void PrintDiskInfo(DiskService& diskService, VgaService& vgaService)
{
    // const FAT32ExtendedBootRecord& extendedRecord = diskService.GetExtendedBootRecord();

    vgaService.SetCursorPos(0, 10);
    vgaService.SetCursorColor(0x0B);
    vgaService.Print("OEM: ");
}
