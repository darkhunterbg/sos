#include "KeyboardSystem.h"
#include "../SystemProvider.h"
#include "../io.h"

namespace input
{
KeyboardSystem::KeyboardSystem()
{
    ps2Controller = new PS2Controller();
    SystemProvider::instance->GetCPUSystem()->GetInterruptor().SetIRQHandler(cpu::IRQType::IRQT_KEYBOARD, KeyboardSystem::KeyboardIRQ);

    keyCodeMapping = new char[255];
    for(int i = 0; i < 255; ++i)
	keyCodeMapping[i] = 0;

    keyCodeMapping[0x0D] = '\t';
    keyCodeMapping[0x0E] = '`';
    keyCodeMapping[0x15] = 'q';
    keyCodeMapping[0x16] = '1';
    keyCodeMapping[0x1A] = 'z';
    keyCodeMapping[0x1B] = 's';
    keyCodeMapping[0x1C] = 'a';
    keyCodeMapping[0x1D] = 'w';
    keyCodeMapping[0x1E] = '2';
    keyCodeMapping[0x21] = 'c';
    keyCodeMapping[0x22] = 'x';
    keyCodeMapping[0x23] = 'd';
    keyCodeMapping[0x24] = 'e';
    keyCodeMapping[0x25] = '4';
    keyCodeMapping[0x26] = '3';
    keyCodeMapping[0x29] = ' ';
    keyCodeMapping[0x2A] = 'v';
    keyCodeMapping[0x2B] = 'f';
    keyCodeMapping[0x2C] = 't';
    keyCodeMapping[0x2D] = 'r';
    keyCodeMapping[0x2E] = '5';
    keyCodeMapping[0x31] = 'n';
    keyCodeMapping[0x32] = 'b';
    keyCodeMapping[0x33] = 'h';
    keyCodeMapping[0x34] = 'g';
    keyCodeMapping[0x35] = 'y';
    keyCodeMapping[0x36] = '6';
    keyCodeMapping[0x3A] = 'm';
    keyCodeMapping[0x3B] = 'j';
    keyCodeMapping[0x3C] = 'u';
    keyCodeMapping[0x3D] = '7';
    keyCodeMapping[0x3E] = '8';
    keyCodeMapping[0x41] = ',';
    keyCodeMapping[0x42] = 'k';
    keyCodeMapping[0x43] = 'i';
    keyCodeMapping[0x44] = 'o';
    keyCodeMapping[0x45] = '0';
    keyCodeMapping[0x46] = '9';
    keyCodeMapping[0x49] = '.';
    keyCodeMapping[0x4A] = '/';
    keyCodeMapping[0x4B] = 'l';
    keyCodeMapping[0x4C] = ';';
    keyCodeMapping[0x4D] = 'p';
    keyCodeMapping[0x4E] = '-';
    keyCodeMapping[0x52] = '\'';
    keyCodeMapping[0x54] = '[';
    keyCodeMapping[0x55] = '=';
    keyCodeMapping[0x5A] = '\n';
    keyCodeMapping[0x5B] = ']';
    keyCodeMapping[0x5D] = '\\';
    keyCodeMapping[0x66] = BACKSPACE;
}

KeyboardSystem::~KeyboardSystem()
{
    delete keyCodeMapping;
    delete ps2Controller;
}

PS2Controller* KeyboardSystem::GetPS2Controller()
{
    return ps2Controller;
}

void KeyboardSystem::ProcessKeycode(byte keycode)
{
    if(skipNext)
	{
		if(keycode == 0x12)
			shift = false;
		
	    skipNext = false;
	    return;
	}
	
	if(keycode == 0x58)
	{
		capslock = !capslock;
		return;
	}

	if(keycode == 0x12)
	{
		shift = true;
		return;
	}

    if(keycode == 0xE0)
	{
	    skipNext = true;
	}
    else if(keycode == 0xF0)
	{
	    skipNext = true;
	}
    else
	{
	    lastKeycode = keycode;
	    hasInput = true;
	}
}
bool KeyboardSystem::PoolInput(char& out)
{
    if(!hasInput)
	return false;

    out = keyCodeMapping[lastKeycode];
	
	bool upper = capslock  ^ shift;
	
	if(upper && (out >='a' && out <='z'))
	{
		out-=32;
	}
	
    hasInput = false;
	
	return true;
}
void KeyboardSystem::KeyboardIRQ(SystemProvider& provider)
{
    byte b = inb((byte)PS2IOPort::PS2IOP_DATA);

    provider.GetKeyboardSystem()->ProcessKeycode(b);


   // provider.GetVGATextSystem()->PrintNumber(b);
    provider.GetCPUSystem()->GetPIC().SendEOI(cpu::IRQType::IRQT_KEYBOARD);
}
}
