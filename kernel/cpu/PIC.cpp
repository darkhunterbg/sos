#include "PIC.h"
#include "../io.h"

namespace cpu
{

PIC::PIC()
{
    Initialize();
}

PIC::~PIC()
{
}

void PIC::Initialize()
{
    byte a1, a2;

    //Save masks
    a1 = inb((byte)PICIOPort::PICIO_MASTER_DATA);
    a2 = inb((byte)PICIOPort::PICIO_SLAVE_DATA);

    //Start initialization
    outb((byte)PICIOPort::PICIO_MASTER_COMMAND, (byte)PICCommand::PICC_INITIALIZE + (byte)PICCommand::PICC_ICW4);
    outb((byte)PICIOPort::PICIO_SLAVE_COMMAND, (byte)PICCommand::PICC_INITIALIZE + (byte)PICCommand::PICC_ICW4);

    //Set vector offsets
    outb((byte)PICIOPort::PICIO_MASTER_DATA, MASTER_VECTOR_OFFSET);
    outb((byte)PICIOPort::PICIO_SLAVE_DATA, SLAVE_VECTOR_OFFSET);

    //Tell Master there is slave at IRQ2 (0000 0100)
    outb((byte)PICIOPort::PICIO_MASTER_DATA, 0b00000100);
    //Tell Salve it has cascade identity (0000 0010)
    outb((byte)PICIOPort::PICIO_SLAVE_DATA, 0b00000010);

    //8086/88 (MCS-80/85) mode
    outb((byte)PICIOPort::PICIO_MASTER_DATA, 0x01);
    outb((byte)PICIOPort::PICIO_SLAVE_DATA, 0x01);

    //Restore masks
    outb((byte)PICIOPort::PICIO_MASTER_DATA, a1);
    outb((byte)PICIOPort::PICIO_SLAVE_DATA, a2);
	
	
	//Set IRQ mask
    outb((byte)PICIOPort::PICIO_MASTER_DATA, 0xfd);
    outb((byte)PICIOPort::PICIO_SLAVE_DATA, 0xff);
}

void PIC::SendEOI(IRQType irq)
{
    if((byte)irq >= 8)
	outb((byte)PICIOPort::PICIO_SLAVE_COMMAND, (byte)PICCommand::PICC_EOI);

    outb((byte)PICIOPort::PICIO_MASTER_COMMAND, (byte)PICCommand::PICC_EOI);
}
}
