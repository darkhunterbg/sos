#include "KeyboardSystem.h"
#include "../SystemProvider.h"
#include "../io.h"


namespace input
{
KeyboardSystem::KeyboardSystem()
{
    ps2Controller = new PS2Controller();
    SystemProvider::instance->GetCPUSystem()->GetInterruptor().SetIRQHandler(cpu::IRQType::IRQT_KEYBOARD ,KeyboardSystem::KeyboardIRQ);
}

KeyboardSystem::~KeyboardSystem()
{
    delete ps2Controller;
}

PS2Controller* KeyboardSystem::GetPS2Controller()
{
    return ps2Controller;
}

void KeyboardSystem::KeyboardIRQ(SystemProvider& provider)
{
    byte b = inb((byte)PS2IOPort::PS2IOP_DATA);
	provider.GetVGATextSystem()->PrintNumber(b);
    provider.GetCPUSystem()->GetPIC().SendEOI(cpu::IRQType::IRQT_KEYBOARD );
}
}
