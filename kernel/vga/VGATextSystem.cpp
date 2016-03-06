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

Cursor& VGATextSystem::GetCursor()
{
    return cursor;
}
}
