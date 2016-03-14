#pragma once
#include "../Types.h"
#include "PS2Controller.h"

class SystemProvider;

namespace input
{
	const char BACKSPACE = '\b';
	
class KeyboardSystem
{
    KeyboardSystem(const& KeyboardSystem) = delete;
    KeyboardSystem& operator=(const& KeyboardSystem) = delete;

  private:
    PS2Controller* ps2Controller = nullptr;
	byte lastKeycode;
	
	char* keyCodeMapping;
	bool hasInput = false;
	bool skipNext = false;
	bool capslock = false;
	bool shift = false;

	static void KeyboardIRQ(SystemProvider& provider);
	void ProcessKeycode(byte keycode);
  public:
    KeyboardSystem();
    ~KeyboardSystem();
	
	PS2Controller* GetPS2Controller();
	bool PoolInput(char& out);
};


}
