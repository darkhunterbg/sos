#pragma once
#include "../Types.h"
#include "PS2Controller.h"

class SystemProvider;

namespace input
{
class KeyboardSystem
{
    KeyboardSystem(const& KeyboardSystem) = delete;
    KeyboardSystem& operator=(const& KeyboardSystem) = delete;

  private:
    PS2Controller* ps2Controller = nullptr;

	static void KeyboardIRQ(SystemProvider& provider);

  public:
    KeyboardSystem();
    ~KeyboardSystem();
	
	PS2Controller* GetPS2Controller();
};


}
