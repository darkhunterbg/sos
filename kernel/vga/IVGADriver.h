#pragma once

#include "Types.h"

namespace vga
{
class IVGADriver
{
    IVGADriver(const& IVGADriver) = delete;
    IVGADriver& operator=(const& IVGADriver) = delete;

  public:
    IVGADriver() = default;
    virtual ~IVGADriver() {}


     virtual bool Print(char symbol, uint x, uint y, uint page, byte color) = 0;
};
}
