#include "SystemProvider.h"

SystemProvider* SystemProvider::instance = nullptr;

SystemProvider::SystemProvider(MemorySystem* ms)
{
    this->memorySystem = ms;
    instance = this;
    vgaTextSystem = new VGATextSystem();
    cpuSystem = new CPUSystem();
    keyboardSystem = new KeyboardSystem();
	fileSystem = new FileSystem();
}

SystemProvider::~SystemProvider()
{
	delete fileSystem;
    delete keyboardSystem;
    delete cpuSystem;
    delete vgaTextSystem;
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
KeyboardSystem* SystemProvider::GetKeyboardSystem()
{
    return keyboardSystem;
}

FileSystem* SystemProvider::GetFileSystem()
{
    return fileSystem;
}
