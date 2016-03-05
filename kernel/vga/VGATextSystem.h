#pragma once

#include "IVGADriver.h"

namespace vga
{
class VGATextSystem
{
    VGATextSystem(const& VGATextSystem) = delete;
    VGATextSystem& operator=(const& VGATextSystem) = delete;

  private:
    IVGADriver* driver = nullptr;

  public:
    VGATextSystem() = default;
    ~VGATextSystem() ;

    void SetDriver(IVGADriver* ownDriver);
	
	void PrintText(const char* text);
};
}
