#include "CPUSystem.h"

namespace cpu
{

CPUSystem::CPUSystem()
{
	pic = new PIC();
	pic->LoadIDT();
}

CPUSystem::~CPUSystem()
{
	delete pic;
}

PIC& CPUSystem::GetPIC()
{
	return *pic;
}

}
