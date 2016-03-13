#pragma once
#include "../Types.h"
#include "PS2Controller.h"

namespace input
{
class KeyboardSystem
{
    KeyboardSystem(const& KeyboardSystem) = delete;
    KeyboardSystem& operator=(const& KeyboardSystem) = delete;

  private:
    PS2Controller* ps2Controller = nullptr;

  public:
    KeyboardSystem();
    ~KeyboardSystem();
	
	PS2Controller* GetPS2Controller();
};
}
