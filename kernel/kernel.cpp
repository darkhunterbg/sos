
int kmain(int argc, char** argv);

int start()
{
    return kmain(0, nullptr);
}

#include "cpp.h"
#include "types.h"
#include "memory/MemorySystem.h"

using namespace memory;

static const uint KERNEL_ADDRESS = 0x10'00'00;            // 1 MB, up to 14 MB for the kernel
static const uint MEMORY_MANAGER_ADDRESS = 0x01'00'00'00; //16 Mb

int kmain(int, char**)
{
    MemorySystem* memorySystem = reinterpret_cast<MemorySystem*>(MEMORY_MANAGER_ADDRESS);
    memorySystem->Initialize();
    memorySystem->DetectMemory();
	
    asm("hlt");

    return 0;
}
