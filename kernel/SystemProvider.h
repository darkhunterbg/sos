#pragma once

#include "memory/MemorySystem.h"
#include "vga/VGATextSystem.h"
#include "cpu/CPUSystem.h"
#include "input/KeyboardSystem.h"

using namespace memory;
using namespace vga;
using namespace cpu;
using namespace input;

static const uint MEMORY_MANAGER_ADDRESS = CPUInterruptor::IDT_ADDRESS+ CPUInterruptor::IDT_SIZE; //16.002 Mb

class SystemProvider
{
    SystemProvider(const& SystemProvider) = delete;
    SystemProvider& operator=(const& SystemProvider) = delete;

  private:
    MemorySystem* memorySystem = nullptr;
    CPUSystem* cpuSystem = nullptr;
    VGATextSystem* vgaTextSystem = nullptr;
	KeyboardSystem* keyboardSystem = nullptr;

    SystemProvider(MemorySystem* ms);

  public:
    static SystemProvider* Create();
	static SystemProvider* instance ;
	
	~SystemProvider();
	
	MemorySystem* GetMemorySystem();
	CPUSystem* GetCPUSystem();
	VGATextSystem* GetVGATextSystem();
	KeyboardSystem* GetKeyboardSystem();
	
	void InitializeSystems();
};


