#pragma GCC diagnostic ignored "-Wpedantic"

void kmain();

int start()
{
    goto*(void*)&kmain;
    return -1;
}

#include "cpp.h"
#include "types.h"
#include "SystemProvider.h"
#include "vga/DefaultVGADriver.h"
#include "io.h"

static const uint KERNEL_ADDRESS = 0x10'00'00; // 1 MB, up to 14 MB for the kernel

extern "C" void irq();

void Interrupt(const CPUException& ex);
void DrawGUI();
void TextInput();

VGATextSystem* v;

void kmain()
{

    SystemProvider* systemProvider = SystemProvider::Create();

    systemProvider->GetVGATextSystem()->SetDriver(new DefaultVGADriver());
    v = systemProvider->GetVGATextSystem();

    v->ClearScreen();

    systemProvider->GetCPUSystem()->GetInterruptor().SetExceptionHandler(Interrupt);
    //cpuSystem->GetPIC().SetIRQHandler(0x77, irq);

    systemProvider->GetCPUSystem()->EnableInterrupts();


    FSEntry buffer[32];
	
	FSEntry root = systemProvider->GetFileSystem()->GetRoot();
	
    uint size = systemProvider->GetFileSystem()->GetEntries(root, buffer, 32);

    systemProvider->GetVGATextSystem()->PrintNumber(size);
    systemProvider->GetVGATextSystem()->PrintChar('\n');

    for(int i = 0; i < size; ++i)
	{
	    systemProvider->GetVGATextSystem()->PrintText(buffer[i].name);
	    systemProvider->GetVGATextSystem()->PrintText(" ID:");
	    systemProvider->GetVGATextSystem()->PrintNumber(buffer[i].id);
	    systemProvider->GetVGATextSystem()->PrintText(" Size:");
		systemProvider->GetVGATextSystem()->PrintNumber(buffer[i].size);
	    systemProvider->GetVGATextSystem()->NewLine();
	}
    systemProvider->GetCPUSystem()->Halt();
    //TextInput();
    //DrawGUI();

    delete systemProvider;
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

void TextInput()
{
    SystemProvider* systemProvider = SystemProvider::instance;

    char c;
    while(true)
	{
	    if(systemProvider->GetKeyboardSystem()->PoolInput(c))
		{
		    if(c == BACKSPACE)
			{
			    systemProvider->GetVGATextSystem()->DeleteLastChar();
			}
		    else
			systemProvider->GetVGATextSystem()->PrintChar(c);
		}
	    else
		{
		    systemProvider->GetCPUSystem()->Halt();
		}
	}
}

void DrawGUI()
{
    SystemProvider* systemProvider = SystemProvider::instance;

    VGATextSystem& vgaSystem = *systemProvider->GetVGATextSystem();

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

	    //x/=0;
	}
}
