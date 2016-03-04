#pragma once

#include "types.h"

namespace utils
{
void Copy(void* source, void* dest, uint size)
{
    byte* s = reinterpret_cast<byte*>(source);
    byte* d = reinterpret_cast<byte*>(dest);

    for(uint i = 0; i < size; ++i)
	{
	    d[i] = s[i];
	}
}
}
