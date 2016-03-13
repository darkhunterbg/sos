#include "VGATextSystem.h"

namespace vga
{
VGATextSystem::~VGATextSystem()
{
    if(driver)
	delete driver;
}

void VGATextSystem::SetDriver(IVGADriver* driver)
{
    if(this->driver)
	delete this->driver;

    this->driver = driver;
}
IVGADriver* VGATextSystem::GetDriver()
{
    return driver;
}

void VGATextSystem::ClearScreen()
{
    driver->ClearScreen(cursor.backgroundColor);
    cursor.x = cursor.y = 0;
}

void VGATextSystem::NewLine()
{
	cursor.x =0;
	++cursor.y;
}

void VGATextSystem::PrintText(const char* text)
{
    byte color = (cursor.backgroundColor << 4) + cursor.foregroundColor;

    const VGAParameters params = driver->GetParameters();

    while(*text != '\0')
	{
	    if(*text == '\n' || *text == '\r')
		{
		    cursor.x = 0;
		    ++cursor.y;
		}
	    else
		{
		    driver->Print(*text, cursor.x, cursor.y, color);
		    ++cursor.x;
		    if(cursor.x == params.textColumns)
			{
			    cursor.x = 0;
			    ++cursor.y;
			}
		}
	    ++text;
	}
}
void VGATextSystem::PrintNumber(uint number, NumberFormatting formatting)
{
    uint tmp = number;
    uint length = 0;
    do
	{
	    ++length;
	    tmp /= (uint)formatting;
	}
    while(tmp > 0);

    char buffer[33];

    int offset = 0;

    if(formatting == NumberFormatting::NF_HEX)
	{
	    buffer[0] = '0';
	    buffer[1] = 'x';
	    offset = 2;
	    for(uint i = 0; i < 8 - length; i++)
		buffer[2 + i] = '0';
	    offset += 8 - length;
	}
    else if(formatting == NumberFormatting::NF_BINARY)
	{
	    buffer[0] = 'b';
	    offset = 1;
		for(uint i = 0; i < 8 - length; i++)
		buffer[1 + i] = '0';
	    offset += 8 - length;
	}
    for(int i = length - 1; i >= 0; --i)
	{
	    uint n = number % (uint)(formatting);

	    buffer[offset + i] = n + '0';
	    if(n > 9)
		buffer[offset + i] += 7;

	    number /= (uint)formatting;
	}

    buffer[length + offset] = '\0';

    PrintText(buffer);
}

Cursor& VGATextSystem::GetCursor()
{
    return cursor;
}
}
