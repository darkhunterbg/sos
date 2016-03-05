#pragma once

#include "Types.h"
#include "memory/MemorySystem.h"


void *operator new(uint size)
{
    return memory::_msInstance->Allocate(size);
}
 
void *operator new[](uint size)
{
     return memory::_msInstance->Allocate(size);
}
 
void operator delete(void *p)
{
   memory::_msInstance->Deallocate(p);
}
 
void operator delete[](void *p)
{
     memory::_msInstance->Deallocate(p);
}
