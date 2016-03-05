#pragma once

#include "IVGADriver.h"

namespace vga
{
class DefaultVGADriver : public IVGADriver
{
  private:
    byte* videoMemory;
	
	uint columnsCount = 80;
	static  const uint VIDEO_MEMORY;
  public:
    DefaultVGADriver();
    ~DefaultVGADriver() = default;

    virtual bool Print(char symbol, uint x, uint y, uint page, byte color) override;
};
}
