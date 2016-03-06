#pragma GCC diagnostic ignored "-Wpedantic"

void kmain();

int start()
{

    goto*(void*)&kmain;
    return -1;
}

#include "cpp.h"
#include "types.h"
#include "memory/MemorySystem.h"
#include "vga/VGATextSystem.h"
#include "vga/DefaultVGADriver.h"
#include "cpu/CPUSystem.h"

using namespace memory;
using namespace vga;
using namespace cpu;

static const uint KERNEL_ADDRESS = 0x10'00'00;                                           // 1 MB, up to 14 MB for the kernel
static const uint MEMORY_MANAGER_ADDRESS = CPUSystem::IDT_ADDRESS + CPUSystem::IDT_SIZE; //16.002 Mb

void Interrupt();

VGATextSystem* v;

void kmain()
{
    MemorySystem* memorySystem = reinterpret_cast<MemorySystem*>(MEMORY_MANAGER_ADDRESS);
    memorySystem->Initialize();
    memorySystem->DetectMemory();

    CPUSystem* cpuSystem = new CPUSystem();
    cpuSystem->Initialize();

    VGATextSystem* vgaTextSystem = new VGATextSystem();
    vgaTextSystem->SetDriver(new DefaultVGADriver());
    v = vgaTextSystem;

    vgaTextSystem->ClearScreen();
    vgaTextSystem->PrintText("Welcome to the real kernel!\n");

    cpuSystem->SetInterruptGate(0x00, (void*)&Interrupt);

    asm("hlt");

    delete vgaTextSystem;
    delete cpuSystem;

    //asm("hlt");
}

void Interrupt()
{
    v->GetCursor().backgroundColor = 1;
    v->ClearScreen();
    v->PrintText("OPS! Just BSODed kinda...");
    asm("hlt");
}
