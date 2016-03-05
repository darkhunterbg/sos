
int kmain(int argc, char** argv);

int start()
{
    return kmain(0, nullptr);
}

#include "types.h"
#include "memory/MemorySystem.h"

using namespace memory;

static const uint KERNEL_ADDRESS = 0x10'00'00; // 1 MB
static const uint MEMORY_MANAGER_ADDRESS = 0x01'00'00'00; //1 Mb

int kmain(int , char**)
{
	MemorySystem* memorySystem = reinterpret_cast<MemorySystem*>(MEMORY_MANAGER_ADDRESS);
	memorySystem->Initialize();
	
	asm("hlt");
	
    return 0;
}
