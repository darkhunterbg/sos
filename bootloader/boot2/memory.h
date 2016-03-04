#pragma once



#include "types.h"

class MemoryService
{
    MemoryService(const MemoryService&) = delete;
    MemoryService& operator=(const MemoryService&) = delete;
	
	//Using simple stack memory manager
	byte* memoryPtr = reinterpret_cast<byte*>(MEMORY_START);
	
	//Loaded address + file cluster size * 2
	const uint MEMORY_START = 0x10000 + 0x1000 * 2;
	const uint ALIGMENT = 0x08;
public:
	MemoryService();
	~MemoryService();
	
	void* Allocate(uint size);
	void Deallocate(void* ptr);
};

extern MemoryService* _msInstance ;

