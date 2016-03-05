#pragma once

#include "Types.h"
#include "memory/MemorySystem.h"

extern "C" void __cxa_pure_virtual()
{
    // Do nothing or print an error message.
}


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
