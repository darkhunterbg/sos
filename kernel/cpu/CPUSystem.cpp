#include "CPUSystem.h"

namespace cpu
{

extern "C" void load_idt();
extern "C" void isr0();

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

void* intFunction;

void CPUSystem::SetInterruptGate(byte gate, void* function)
{
	intFunction = function;
	
	 idtTable[gate] = {
	        (ushort)(((uint)&isr0) & 0xFFFF),
	        8,
	        0,
	        0b10001110,
	        (ushort)(((uint)&isr0 >> 16) & 0xFFFF),
	    };
}

void CPUSystem::DefaultInterruptHandle()
{
    asm("hlt");
}

void _fault(regs *r)
{
	typedef void(*Action)(const regs&);
	
	((Action)intFunction)(*r);
}

void _trap(regs *r)
{
	typedef void(*Action)(const regs&);
	
	((Action)intFunction)(*r);
}

void _abort(regs *r)
{
	typedef void(*Action)(const regs&);
	
	((Action)intFunction)(*r);
}


}
