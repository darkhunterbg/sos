#pragma once

#include "types.h"

struct Cursor
{
    uint x = 0, y = 0;
    byte color = 0x1F;
};

class VgaService
{
    VgaService(const VgaService&) = delete;
    VgaService& operator=(const VgaService&) = delete;

  private:
    Cursor cursor;
    byte* videoMemory = reinterpret_cast<byte*>(VgaService::VIDEO_MEMORY);

   static  const uint VIDEO_MEMORY = 0xB'80'00;

  public:
    static const uint COLUMNS = 80;
    static const uint LINES = 25;
    static const uint PAGES = 8;

  public:
    VgaService();
    ~VgaService();

    void ClearScreen(byte color);
    void Print(const char* text, uint size = 0);
    void Print(char c);
    void Print(uint n);
};
