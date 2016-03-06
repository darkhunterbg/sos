#pragma once

#include "IVGADriver.h"

namespace vga
{

struct Cursor
{
    uint x = 0;
    uint y = 0;
    byte foregroundColor = 0xF;
    byte backgroundColor = 0;
};

class VGATextSystem
{
    VGATextSystem(const& VGATextSystem) = delete;
    VGATextSystem& operator=(const& VGATextSystem) = delete;

  private:
    IVGADriver* driver = nullptr;
    Cursor cursor;

  public:
    VGATextSystem() = default;
    ~VGATextSystem();

    void SetDriver(IVGADriver* ownDriver);
    IVGADriver* GetDriver();
    void PrintText(const char* text);
    void ClearScreen();

    Cursor& GetCursor();
};
}
