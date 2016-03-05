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

void VGATextSystem::PrintText(const char* text)
{
    int x = 0;
    while(*text != '\0')
	{
	    driver->Print(*text, x, 0, 0, 0x0F);
		++x;
		++text;
	}
}
}
