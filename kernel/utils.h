#pragma once

#include "types.h"

namespace utils
{
void Copy(const void* source, void* dest, uint size)
{
    const byte* s = reinterpret_cast<const byte*>(source);
    byte* d = reinterpret_cast<byte*>(dest);

    for(uint i = 0; i < size; ++i)
	{
	    d[i] = s[i];
	}
}
uint StringCopy(const char* s, char* d, uint size)
{
    for(uint i = 0; i < size; ++i)
	{
	    d[i] = s[i];
	    if(s[i] == 0)
		return i;
	}

    d[size] = 0;

    return size;
}


uint StringAppend(const char* s, char* d, uint sSize, uint dSize)
{
    for(uint i = 0; i < dSize; ++i)
	{
	    if(d[i] == 0)
		{
		    return i + StringCopy(s, d + i, sSize);
		}
	}
    return dSize;
}

int FindChar(const char* s, char c, uint sSize)
{
    for(uint i = 0; i < sSize; ++i)
	{
	    if(s[i] == c)
		{
		    return i;
		}
	}
    return -1;
}

bool Compare(const void* a, const void* b, uint count)
{
    for(uint i = 0; i < count; ++i)
	if(((byte*)a)[i] != ((byte*)b)[i])
	    return false;

    return true;
}
}
