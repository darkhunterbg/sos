#include "PS2Controller.h"
#include "../io.h"
#include "../SystemProvider.h"

namespace input
{
PS2Controller::PS2Controller()
{
    //Disable ports
    outb((byte)PS2IOPort::PS2IOP_STATUS_COMMAND, (byte)PS2Command::PS2C_DISABLE_FIRST);
    outb((byte)PS2IOPort::PS2IOP_STATUS_COMMAND, (byte)PS2Command::PS2C_DISABLE_SECOND);

    //Flush buffer
    inb((byte)PS2IOPort::PS2IOP_DATA);

    //Set Controller configuration
    //Disable IRQ and translation

    outb((byte)PS2IOPort::PS2IOP_STATUS_COMMAND, (byte)PS2Command::PS2C_READ_BYTE_0);
    config = inb((byte)PS2IOPort::PS2IOP_DATA);

    config &= ~((byte)PS2Configuration::PS2C_INTERRUPT_FIRST | (byte)PS2Configuration::PS2C_CLOCK_SECOND | (byte)PS2Configuration::PS2C_TRANSLATION_FIRST);

    outb((byte)PS2IOPort::PS2IOP_STATUS_COMMAND, (byte)PS2Command::PS2C_WRITE_BYTE_0);
    outb((byte)PS2IOPort::PS2IOP_DATA, (byte)config);

    //Test Controller
    outb((byte)PS2IOPort::PS2IOP_STATUS_COMMAND, (byte)PS2Command::PS2C_TEST_CONTROLLER);

    status = 0;

    do
	{
	    status = inb((byte)PS2IOPort::PS2IOP_DATA);
	    //v->NewLine();
	    //v->PrintNumber(status, NumberFormatting::NF_HEX);
	    //0xFC = failed
	}
    while(status != 0x55 && status != 0xFC); //Passed

    //Test first port

    outb((byte)PS2IOPort::PS2IOP_STATUS_COMMAND, (byte)PS2Command::PS2C_TEST_FIRST);

    do
	{
	    status = inb((byte)PS2IOPort::PS2IOP_DATA);
	    //1,2,3,4 - failed
	}
    while(status >= 4); //Passed

    //Enable port and IRQ

    config |= ((byte)PS2Configuration::PS2C_INTERRUPT_FIRST);
    outb((byte)PS2IOPort::PS2IOP_STATUS_COMMAND, (byte)PS2Command::PS2C_WRITE_BYTE_0);
    outb((byte)PS2IOPort::PS2IOP_DATA, (byte)config);

    outb((byte)PS2IOPort::PS2IOP_STATUS_COMMAND, (byte)PS2Command::PS2C_ENABLE_FIRST);
}

PS2Controller::~PS2Controller()
{
}
}
