#pragma once

#include "../Types.h"
#include "PIC.h"

namespace cpu
{

struct CPURegisters
{
    uint gs, fs, es, ds;                         
    uint edi, esi, ebp, esp, ebx, edx, ecx, eax; 
};

enum class GDTSegmentType : ushort
{
	GDTST_CODE = 0x08,
	GDTST_DATA = 0x10
};

class CPUSystem
{
    CPUSystem(const& CPUSystem) = delete;
    CPUSystem& operator=(const& CPUSystem) = delete;

	 PIC* pic = nullptr;

  public:
    CPUSystem();
    ~CPUSystem();

    PIC& GetPIC();
};


}
