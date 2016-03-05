#pragma once

#include "types.h"

namespace utils
{
void Copy(const void* source, void* dest, uint size);
bool Compare(const void* a, const void* b, uint count);
}
