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

static const uint KERNEL_ADDRESS = 0x10'00'00;                               // 1 MB, up to 14 MB for the kernel
static const uint MEMORY_MANAGER_ADDRESS = PIC::IDT_ADDRESS + PIC::IDT_SIZE; //16.002 Mb

extern "C" void irq();

void Interrupt(const CPUException& ex);
void IRQHandler();
void DrawGUI(VGATextSystem&);

VGATextSystem* v;

void kmain()
{

    MemorySystem* memorySystem = reinterpret_cast<MemorySystem*>(MEMORY_MANAGER_ADDRESS);
    memorySystem->Initialize();
    memorySystem->DetectMemory();

    CPUSystem* cpuSystem = new CPUSystem();

    VGATextSystem* vgaTextSystem = new VGATextSystem();
    vgaTextSystem->SetDriver(new DefaultVGADriver());
    v = vgaTextSystem;

    vgaTextSystem->ClearScreen();

    cpuSystem->GetPIC().SetExceptionHandler(Interrupt);
   // cpuSystem->GetPIC().SetIRQHandler(0x77, irq);

   // asm("sti");

    DrawGUI(*vgaTextSystem);

    delete vgaTextSystem;
    delete cpuSystem;
}

void IRQHandler()
{

}

void Interrupt(const CPUException& ex)
{
    v->GetCursor().foregroundColor = 0x0F;
    v->GetCursor().backgroundColor = 1;
    v->ClearScreen();
    v->PrintText("Something went puff!\n");

    v->PrintText("Message: ");
    v->PrintText(ex.exceptionMessage);
    v->PrintText("\n");

    v->PrintText("Interrupt:");
    v->PrintNumber(ex.exceptionData->int_no, NumberFormatting::NF_HEX);
    v->PrintText(" Error Code:");
    v->PrintNumber(ex.exceptionData->int_no, NumberFormatting::NF_HEX);

    v->PrintText("\nDS:");
    v->PrintNumber(ex.exceptionData->ds, NumberFormatting::NF_HEX);
    v->PrintText(" ES:");
    v->PrintNumber(ex.exceptionData->es, NumberFormatting::NF_HEX);
    v->PrintText(" FS:");
    v->PrintNumber(ex.exceptionData->fs, NumberFormatting::NF_HEX);
    v->PrintText(" GS:");
    v->PrintNumber(ex.exceptionData->gs, NumberFormatting::NF_HEX);

    v->PrintText("\nEDI:");
    v->PrintNumber(ex.exceptionData->edi, NumberFormatting::NF_HEX);
    v->PrintText(" ESI:");
    v->PrintNumber(ex.exceptionData->esi, NumberFormatting::NF_HEX);
    v->PrintText(" EBP:");
    v->PrintNumber(ex.exceptionData->ebp, NumberFormatting::NF_HEX);
    v->PrintText(" ESP:");
    v->PrintNumber(ex.exceptionData->esp, NumberFormatting::NF_HEX);
    v->PrintText("\nEAX:");
    v->PrintNumber(ex.exceptionData->eax, NumberFormatting::NF_HEX);
    v->PrintText(" EBX:");
    v->PrintNumber(ex.exceptionData->ebx, NumberFormatting::NF_HEX);
    v->PrintText(" ECX:");
    v->PrintNumber(ex.exceptionData->ecx, NumberFormatting::NF_HEX);
    v->PrintText(" EDX:");
    v->PrintNumber(ex.exceptionData->edx, NumberFormatting::NF_HEX);

    v->PrintText("\nEIP:");
    v->PrintNumber(ex.exceptionData->eip, NumberFormatting::NF_HEX);
    v->PrintText(" CS:");
    v->PrintNumber(ex.exceptionData->cs, NumberFormatting::NF_HEX);
    v->PrintText(" EFLAGS:");
    v->PrintNumber(ex.exceptionData->eflags, NumberFormatting::NF_HEX);
    v->PrintText(" USERESP:");
    v->PrintNumber(ex.exceptionData->useresp, NumberFormatting::NF_HEX);
    v->PrintText(" SS:");
    v->PrintNumber(ex.exceptionData->ss, NumberFormatting::NF_HEX);

    while(true)
	;

    //change address in EIP to jmp to kernel entry/ recovering from errr
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

	     x/=0;
	}
}
