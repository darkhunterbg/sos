#pragma once

#include "Types.h"

namespace vga
{
struct VGAPalette
{
    byte* colors;
    uint colorsCount;
};
struct VGAParameters
{
    uint textColumns;
    uint textRows;
};

class IVGADriver
{
    IVGADriver(const& IVGADriver) = delete;
    IVGADriver& operator=(const& IVGADriver) = delete;

  public:
    IVGADriver() = default;
    virtual ~IVGADriver()
    {
    }

    virtual void Print(char symbol, uint x, uint y, byte color) = 0;
	virtual void ClearScreen(byte color) = 0;
    virtual const VGAPalette& GetPalette() const = 0;
    virtual const VGAParameters& GetParameters() const = 0;
};
}
