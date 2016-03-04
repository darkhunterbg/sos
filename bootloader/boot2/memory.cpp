#include "memory.h"

MemoryService* _msInstance = nullptr;

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
void MemoryService::Copy(void* source, void* dest, uint size) const
{
    byte* s = reinterpret_cast<byte*>(source);
    byte* d = reinterpret_cast<byte*>(dest);

    for(uint i = 0; i < size; ++i)
	{
	    d[i] = s[i];
	}
}
