#include "SystemProvider.h"

SystemProvider::SystemProvider(MemorySystem* ms)
{
    this->memorySystem = ms;
    cpuSystem = new CPUSystem();
    vgaTextSystem = new VGATextSystem();
}

SystemProvider::~SystemProvider()
{
    delete vgaTextSystem;
    delete cpuSystem;
}

SystemProvider* SystemProvider::Create()
{
    MemorySystem* memorySystem = reinterpret_cast<MemorySystem*>(MEMORY_MANAGER_ADDRESS);

    memorySystem->Initialize();
    memorySystem->DetectMemory();

    return new SystemProvider(memorySystem);
}

void SystemProvider::InitializeSystems()
{
    memorySystem->DetectMemory();
}

MemorySystem* SystemProvider::GetMemorySystem()
{
    return memorySystem;
}
CPUSystem* SystemProvider::GetCPUSystem()
{
    return cpuSystem;
}
VGATextSystem* SystemProvider::GetVGATextSystem()
{
    return vgaTextSystem;
}
