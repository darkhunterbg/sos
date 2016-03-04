#include "memory.h"

MemoryService::MemoryService()
{
    memoryPtr = reinterpret_cast<byte*>(MEMORY_START);
}
MemoryService::~MemoryService()
{
}

void* MemoryService::Allocate(uint size)
{
    byte* result = memoryPtr;

    memoryPtr += size;
    uint off = size % ALIGMENT;

    if(off)
	memoryPtr += ALIGMENT - off;

    return static_cast<void*>(result);
}
void MemoryService::Deallocate(void* )
{
	
    //Nothing we can do :(
}
