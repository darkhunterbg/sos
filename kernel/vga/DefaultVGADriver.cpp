#include "DefaultVGADriver.h"

namespace vga
{
const uint DefaultVGADriver::VIDEO_MEMORY = 0xB'80'00;

DefaultVGADriver::DefaultVGADriver()
{
    videoMemory = reinterpret_cast<byte*>(DefaultVGADriver::VIDEO_MEMORY);

    parameters.textColumns = 80;
    parameters.textRows = 25;

    palette.colorsCount = 16;
    palette.colors = new byte[palette.colorsCount];
    for(uint i = 0; i < palette.colorsCount; ++i)
	{
	    palette.colors[i] = static_cast<byte>(i);
	}
}
DefaultVGADriver::~DefaultVGADriver()
{
    delete palette.colors;
}

void DefaultVGADriver::Print(char symbol, uint x, uint y, byte color)
{
    volatile byte* writeAddress = videoMemory + x * 2 + y * 2 * parameters.textColumns;
    *writeAddress = symbol;
    ++writeAddress;
    *writeAddress = color;
}
void DefaultVGADriver::ClearScreen(byte color)
{
    color = color << 4;

    for(uint i = 0; i < parameters.textRows * parameters.textColumns * 2; i += 2)
	{
	    videoMemory[i] = ' ';
	    videoMemory[i + 1] = color;
	}
}

const VGAPalette& DefaultVGADriver::GetPalette() const
{
    return palette;
}
const VGAParameters& DefaultVGADriver::GetParameters() const
{
    return parameters;
}
}
