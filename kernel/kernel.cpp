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

void Interrupt(const regs& r);
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

    //TestMethod();
    //vgaTextSystem->PrintText("Welcome to the real kernel!\n");

    cpuSystem->SetInterruptGate(0x00, (void*)&Interrupt);

    DrawGUI(*vgaTextSystem);

    asm("hlt");

    delete vgaTextSystem;
    delete cpuSystem;

    //asm("hlt");
}

void Interrupt(const regs& r)
{
	v->GetCursor().foregroundColor = 0x0F;
    v->GetCursor().backgroundColor = 1;
    v->ClearScreen();
    v->PrintText("Something went puff!\n");

   v->PrintText("DivisionByZeroException\n");

    v->PrintText("Interrupt:");
    v->PrintNumber(r.int_no, NumberFormatting::NF_HEX);
    v->PrintText(" Error Code:");
    v->PrintNumber(r.int_no, NumberFormatting::NF_HEX);

    v->PrintText("\nDS:");
    v->PrintNumber(r.ds, NumberFormatting::NF_HEX);
    v->PrintText(" ES:");
    v->PrintNumber(r.es, NumberFormatting::NF_HEX);
    v->PrintText(" FS:");
    v->PrintNumber(r.fs, NumberFormatting::NF_HEX);
    v->PrintText(" GS:");
    v->PrintNumber(r.gs, NumberFormatting::NF_HEX);

    v->PrintText("\nEDI:");
    v->PrintNumber(r.edi, NumberFormatting::NF_HEX);
    v->PrintText(" ESI:");
    v->PrintNumber(r.esi, NumberFormatting::NF_HEX);
    v->PrintText(" EBP:");
    v->PrintNumber(r.ebp, NumberFormatting::NF_HEX);
    v->PrintText(" ESP:");
    v->PrintNumber(r.esp, NumberFormatting::NF_HEX);
    v->PrintText("\nEAX:");
    v->PrintNumber(r.eax, NumberFormatting::NF_HEX);
    v->PrintText(" EBX:");
    v->PrintNumber(r.ebx, NumberFormatting::NF_HEX);
    v->PrintText(" ECX:");
    v->PrintNumber(r.ecx, NumberFormatting::NF_HEX);
    v->PrintText(" EDX:");
    v->PrintNumber(r.edx, NumberFormatting::NF_HEX);

    v->PrintText("\nEIP:");
    v->PrintNumber(r.eip, NumberFormatting::NF_HEX);
    v->PrintText(" CS:");
    v->PrintNumber(r.cs, NumberFormatting::NF_HEX);
    v->PrintText(" EFLAGS:");
    v->PrintNumber(r.eflags, NumberFormatting::NF_HEX);
    v->PrintText(" USERESP:");
    v->PrintNumber(r.useresp, NumberFormatting::NF_HEX);
    v->PrintText(" SS:");
    v->PrintNumber(r.ss, NumberFormatting::NF_HEX);

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

	    x /= 0;
	}
}
