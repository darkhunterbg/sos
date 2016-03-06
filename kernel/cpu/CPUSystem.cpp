#include "CPUSystem.h"

namespace cpu
{

extern "C" void load_idt();

CPUSystem::CPUSystem()
{
}

CPUSystem::~CPUSystem()
{
}

void CPUSystem::Initialize()
{
    idtTable = (IDTDescriptor*)IDT_ADDRESS;

   /* for(int i = 0; i < IDT_COUNT; ++i)
	{
	    idtTable[i] = {
	        (ushort)(((uint)&CPUSystem::DefaultInterruptHandle) & 0xFFFF),
	        8,
	        0,
	        0b10001110,
	        (ushort)(((uint)&CPUSystem::DefaultInterruptHandle >> 16) & 0xFFFF),
	    };
	}*/

    load_idt();
}

void CPUSystem::SetInterruptGate(byte gate, void* function)
{
	 idtTable[gate] = {
	        (ushort)(((uint)function) & 0xFFFF),
	        8,
	        0,
	        0b10001110,
	        (ushort)(((uint)function >> 16) & 0xFFFF),
	    };
}

void CPUSystem::DefaultInterruptHandle()
{
    asm("hlt");
}
}
