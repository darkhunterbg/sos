#pragma GCC diagnostic ignored "-Wpedantic"

void kmain();

int start()
{

    goto*(void*)&kmain;
    return -1;
}

#include "cpp.h"
#include "types.h"
#include "memory/MemorySystem.h"
#include "vga/VGATextSystem.h"
#include "vga/DefaultVGADriver.h"
#include "cpu/CPUSystem.h"

using namespace memory;
using namespace vga;
using namespace cpu;

static const uint KERNEL_ADDRESS = 0x10'00'00;                                           // 1 MB, up to 14 MB for the kernel
static const uint MEMORY_MANAGER_ADDRESS = CPUSystem::IDT_ADDRESS + CPUSystem::IDT_SIZE; //16.002 Mb

void Interrupt();
void DrawGUI(VGATextSystem&);

VGATextSystem* v;

void kmain()
{
    MemorySystem* memorySystem = reinterpret_cast<MemorySystem*>(MEMORY_MANAGER_ADDRESS);
    memorySystem->Initialize();
    memorySystem->DetectMemory();

    CPUSystem* cpuSystem = new CPUSystem();
    cpuSystem->Initialize();

    VGATextSystem* vgaTextSystem = new VGATextSystem();
    vgaTextSystem->SetDriver(new DefaultVGADriver());
    v = vgaTextSystem;

    vgaTextSystem->ClearScreen();

    //vgaTextSystem->PrintText("Welcome to the real kernel!\n");

    cpuSystem->SetInterruptGate(0x00, (void*)&Interrupt);

    DrawGUI(*vgaTextSystem);

    asm("hlt");

    delete vgaTextSystem;
    delete cpuSystem;

    //asm("hlt");
}

void Interrupt()
{
    v->GetCursor().backgroundColor = 1;
    v->ClearScreen();
    v->PrintText("OPS! Just BSODed kinda...");
    asm("hlt");
}

void DrawGUI(VGATextSystem& vgaSystem)
{
    Cursor& cursor = vgaSystem.GetCursor();

    cursor.foregroundColor = 0x07;
    cursor.x = 16;
    cursor.y = 3;

    vgaSystem.PrintText("+-----------------------------------------+");
    cursor.x = 16;
    cursor.y = 4;
    vgaSystem.PrintText("|    SOS 32 Bit C++ Kernel Executing!     |");
    cursor.x = 16;
    cursor.y = 5;
    vgaSystem.PrintText("+-----------------------------------------+");

    cursor.x = 15;
    cursor.y = 10;
    cursor.foregroundColor = 0x0F;
    vgaSystem.PrintText("I am preparing to load... Hold on, please... :)");

    byte a = 0x00;
    byte b = 0x10;

    while(true)
	{
	    uint x = 0;
	    cursor.foregroundColor = b;
	    byte c = a;
	    a = b;
	    b = c;
	    for(uint i = 0; i < vgaSystem.GetDriver()->GetParameters().textColumns; ++i)
		{
		    for(uint j = 0; j < 100000; ++j)
			{
			    cursor.y = 22;
			    cursor.x = x;
			}
		    vgaSystem.PrintText(" ");
		    ++x;
		}
	}
}
