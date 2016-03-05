#include "memory/MemorySystem.h"

namespace memory
{
	MemorySystem* _msInstance = nullptr;
	
void MemorySystem::Initialize()
{
    //'this' address will be where the object is placed

    allocatedPointer = reinterpret_cast<uint>(this);
	allocatedPointer += sizeof(MemorySystem);
	_msInstance = this;
}

void MemorySystem::DetectMemory()
{
    //Do some magic with BIOS, in the future

    maxMemory = 511 * 1024 * 1024;
}

void* MemorySystem::Allocate(uint size)
{
	uint result = allocatedPointer;
    allocatedPointer += size;
    return reinterpret_cast<void*>(result);
}
void MemorySystem::Deallocate(void*)
{
    //Do nothing
}
}
