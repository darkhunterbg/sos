#include "vga.h"

VgaService::VgaService()
{
     videoMemory = reinterpret_cast<byte*>(VgaService::VIDEO_MEMORY);
}
VgaService::~VgaService()
{
}

void VgaService::ClearScreen(byte color)
{
    for(uint i = 0; i < COLUMNS * LINES * 2; i += 2)
	{
	    videoMemory[i] = ' ';
	    videoMemory[i + 1] = color;
	}

    SetCursorPos(0, 0);
}
void VgaService::SetCursorPos(uint x, uint y)
{
    cursor.x = x;
    cursor.y = y;
}
void VgaService::Print(const char* text)
{

    const char* ptr = text;
    while(*ptr != '\0')
	{
	    PrintChar(*ptr);
	    ++ptr;
	}
}
void VgaService::PrintChar(char c)
{
    if(c == 0)
	return;

    if(c == '\n' || c == '\r')
	{
	    ++cursor.y;
	    cursor.x = 0;
	    return;
	}

    byte* writeAddress = videoMemory + (cursor.x) * 2 + cursor.y * 2 * COLUMNS;
    *writeAddress = c;
    ++writeAddress;
    *writeAddress = cursor.color;

    ++cursor.x;

    if(cursor.x == COLUMNS)
	{
	    ++cursor.y;
	    cursor.x = 0;
	}
}
void VgaService::SetCursorColor(byte color)
{
    cursor.color = color;
}
