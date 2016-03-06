#pragma GCC diagnostic ignored "-Wpedantic"

void kmain();

int start()
{
	
	
     goto *(void*)&kmain;
	 return -1;
}

#include "cpp.h"
#include "types.h"
#include "memory/MemorySystem.h"
#include "vga/VGATextSystem.h"
#include "vga/DefaultVGADriver.h"

using namespace memory;
using namespace vga;

static const uint KERNEL_ADDRESS = 0x10'00'00;            // 1 MB, up to 14 MB for the kernel
static const uint MEMORY_MANAGER_ADDRESS = 0x01'00'00'00; //16 Mb

void kmain()
{
    MemorySystem* memorySystem = reinterpret_cast<MemorySystem*>(MEMORY_MANAGER_ADDRESS);
    memorySystem->Initialize();
    memorySystem->DetectMemory();
	
	VGATextSystem* vgaTextSystem = new VGATextSystem();
	vgaTextSystem->SetDriver(new DefaultVGADriver());
	
	vgaTextSystem->PrintText("Welcome to the real kernel!");
	
	delete vgaTextSystem;
	
    asm("hlt");
}
