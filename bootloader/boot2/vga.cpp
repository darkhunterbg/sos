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
void VgaService::Print(const char* text, uint size)
{
    if(size)
	{
	    for(uint i = 0; i < size; ++i)
		{
		    if(*text == '\0')
			break;
		    Print(*text);
		    ++text;
		}
	}
    else
	{
	    while(*text != '\0')
		{
		    Print(*text);
		    ++text;
		}
	}
}

void VgaService::Print(char c)
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
void VgaService::Print(uint n)
{
    uint tmp = n;
    uint length = 0;
    do
	{
	    ++length;
	    tmp /= 10;
	}
    while(tmp > 0);

    char buffer[32];

    for(int i = length - 1; i >= 0; --i)
	{
	    buffer[i] = n % 10 + '0';
	    n /= 10;
	}

    buffer[length] = '\0';

    Print(buffer);
}

void VgaService::SetCursorColor(byte color)
{
    cursor.color = color;
}
