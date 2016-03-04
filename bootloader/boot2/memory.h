#pragma once



#include "types.h"

class MemoryService
{
    MemoryService(const MemoryService&) = delete;
    MemoryService& operator=(const MemoryService&) = delete;
	
	//Using simple stack memory manager
	byte* memoryPtr = reinterpret_cast<byte*>(MEMORY_START);
	
	//Loaded address + file cluster size
	const uint MEMORY_START = 0x10000 + 0x1000 ;
	const uint ALIGMENT = 0x08;
public:
	MemoryService();
	~MemoryService();
	
	void* Allocate(uint size);
	Deallocate(void* ptr);
	void Copy(void* source, void* dest, uint sourceSize) const;
};

extern MemoryService* _msInstance ;

