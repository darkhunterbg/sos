#include "DefaultVGADriver.h"

namespace vga
{
const uint DefaultVGADriver::VIDEO_MEMORY = 0xB'80'00;

DefaultVGADriver::DefaultVGADriver()
{
    videoMemory = reinterpret_cast<byte*>(DefaultVGADriver::VIDEO_MEMORY);
}

bool DefaultVGADriver::Print(char symbol, uint x, uint y, uint , byte color)
{
    byte* writeAddress = videoMemory + x * 2 + y * 2 * columnsCount;
    *writeAddress = symbol;
    ++writeAddress;
    *writeAddress = color;
    return true;
}
}
