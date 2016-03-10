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
CPUInterruptor& CPUSystem::GetInterruptor()
{
    return *interruptor;
}
}
