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

    VgaService vgaService;

    vgaService.ClearScreen(0x00);
    vgaService.SetCursorColor(0x07);
    vgaService.SetCursorPos(16, 6);

    vgaService.Print("+-----------------------------------------+");
    vgaService.SetCursorPos(16, 7);
    vgaService.Print("|    SOS 32 Bit C++ Kernel Executing!     |");
    vgaService.SetCursorPos(16, 8);
    vgaService.Print("+-----------------------------------------+");

    vgaService.SetCursorPos(16, 16);
    vgaService.SetCursorColor(0x0F);
    vgaService.Print("I am preparing to load... Hold on, please... :)");
    vgaService.SetCursorPos(0, 20);

    uint x = 0;
    for(uint i = 0; i < 320; ++i)
	{
	    for(uint j = 0; j < 100000; ++j)
		{
		    vgaService.SetCursorPos(x, 20);
		}
	    vgaService.PrintChar('=');
	    ++x;
	}

    asm("hlt");
}
