#include "CPUSystem.h"

namespace cpu
{

CPUSystem::CPUSystem()
{
    interruptor = new CPUInterruptor();
    interruptor->LoadIDT();

    pic = new PIC();
}

CPUSystem::~CPUSystem()
{
    delete pic;

    delete interruptor;
}

PIC& CPUSystem::GetPIC()
{
    return *pic;
}

void CPUSystem::Halt()
{
	asm("hlt");
}
void CPUSystem::EnableInterrupts()
{
	asm("sti");
}

CPUInterruptor& CPUSystem::GetInterruptor()
{
    return *interruptor;
}
}
