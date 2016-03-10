#pragma once

#include "Types.h"


extern "C" void outb(ushort port, byte value);
extern "C" void outw(ushort port, ushort value);
extern "C" void outdw(ushort port, uint value);

extern "C" byte inb(ushort port);
extern "C" ushort inw(ushort port);
extern "C" uint indw(ushort port);
