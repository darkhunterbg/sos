#include "KeyboardSystem.h"

namespace input
{
	KeyboardSystem::KeyboardSystem()
	{
		ps2Controller = new PS2Controller();
	}
	
	KeyboardSystem::~KeyboardSystem()
	{
		delete ps2Controller;
	}
	
	PS2Controller* KeyboardSystem::GetPS2Controller()
	{
		return ps2Controller;
	}
}
