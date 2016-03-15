#include "ATAController.h"
#include "../SystemProvider.h"
#include "../io.h"

namespace fs
{
ATAController::ATAController()
{
    SystemProvider::instance->GetCPUSystem()->GetInterruptor().SetIRQHandler(cpu::IRQType::IRQT_ATA_PRIMARY, ATAController::PrimaryHandler);

    //Disable interrupts
    outb((ushort)ATAIOPort::ATAIOP_CONTROL_ALT_STATUS, (byte)ATAIOCommand::ATAIOC_C_NO_INTERRUPTS);
}

ATAController::~ATAController()
{
}

bool ATAController::Poll()
{
    while(true)
	{
	    byte status = inb((ushort)ATAIOPort::ATAIOP_COMMAND_STATUS);

	    //if(status = 0xFF)
	    {
		//Something aint right
		//return false;
	    }
	    //vga->SetCursorPos(0,0);
	    //vga->Print(static_cast<uint>(status));

	    if(status & (byte)ATAStatus::ATAS_BUSY)
		continue;

	    if(status & (byte)ATAStatus::ATAS_ERROR || status & (byte)ATAStatus::ATAS_DRIVE_FAULT)
		return false;

	    if(status & (byte)ATAStatus::ATAS_READY)
		return true;
	};
}

bool ATAController::Read(ulong startSector, ushort lengthSectors, byte* buffer)
{

    outb((ushort)ATAIOPort::ATAIOP_DRIVE_SELECT, (byte)ATAIOCommand::ATAIOC_DRIVE_RW);

    byte sectorsHigh = lengthSectors >> 8 & 0xFF;
    byte sectorsLow = lengthSectors & 0xFF;

    byte lba[6];

    for(uint i = 0; i < 6; ++i)
	{
	    lba[i] = startSector & 0xFF;
	    startSector = startSector >> 8;
	}

    outb((ushort)ATAIOPort::ATAIOP_SECTOR_COUNT, sectorsHigh);
    outb((ushort)ATAIOPort::ATAIOP_LBA_LOW, lba[3]);
    outb((ushort)ATAIOPort::ATAIOP_LBA_MID, lba[4]);
    outb((ushort)ATAIOPort::ATAIOP_LBA_HIGH, lba[5]);
    outb((ushort)ATAIOPort::ATAIOP_SECTOR_COUNT, sectorsLow);
    outb((ushort)ATAIOPort::ATAIOP_LBA_LOW, lba[0]);
    outb((ushort)ATAIOPort::ATAIOP_LBA_MID, lba[1]);
    outb((ushort)ATAIOPort::ATAIOP_LBA_HIGH, lba[2]);

    outb((ushort)ATAIOPort::ATAIOP_COMMAND_STATUS, (byte)ATAIOCommand::ATAIOC_READ_LBA48);

    for(ushort s = 0; s < lengthSectors; ++s)
	{
	    // SystemProvider::instance->GetVGATextSystem()->ClearScreen();
	      if(!Poll())
	    return false;

	    for(uint i = 0; i < 256; ++i)
		{
		    ushort data = inw((ushort)ATAIOPort::ATAIOP_DATA);

		    buffer[0] = data & 0xFF;
		    buffer[1] = data >> 8 & 0xFF;
		    buffer += 2;
		}
	}

   // outb((ushort)ATAIOPort::ATAIOP_COMMAND_STATUS, (byte)ATAIOCommand::ATAIOC_FLUSH);

    return true;
}

bool ATAController::Write(ulong startSector, ushort lengthSectors, const byte* buffer)
{
	
	
    outb((ushort)ATAIOPort::ATAIOP_DRIVE_SELECT, (byte)ATAIOCommand::ATAIOC_DRIVE_RW);

    byte sectorsHigh = lengthSectors >> 8 & 0xFF;
    byte sectorsLow = lengthSectors & 0xFF;

    byte lba[6];

    for(uint i = 0; i < 6; ++i)
	{
	    lba[i] = startSector & 0xFF;
	    startSector = startSector >> 8;
	}

    outb((ushort)ATAIOPort::ATAIOP_SECTOR_COUNT, sectorsHigh);
    outb((ushort)ATAIOPort::ATAIOP_LBA_LOW, lba[3]);
    outb((ushort)ATAIOPort::ATAIOP_LBA_MID, lba[4]);
    outb((ushort)ATAIOPort::ATAIOP_LBA_HIGH, lba[5]);
    outb((ushort)ATAIOPort::ATAIOP_SECTOR_COUNT, sectorsLow);
    outb((ushort)ATAIOPort::ATAIOP_LBA_LOW, lba[0]);
    outb((ushort)ATAIOPort::ATAIOP_LBA_MID, lba[1]);
    outb((ushort)ATAIOPort::ATAIOP_LBA_HIGH, lba[2]);

    outb((ushort)ATAIOPort::ATAIOP_COMMAND_STATUS, (byte)ATAIOCommand::ATAIOC_WRITE_LBA48);

    for(ushort s = 0; s < lengthSectors; ++s)
	{
	    // SystemProvider::instance->GetVGATextSystem()->ClearScreen();
	      if(!Poll())
	    return false;

	    for(uint i = 0; i < 256; ++i)
		{
			ushort word =*(ushort*)(buffer + i * 2);
			
		    outw((ushort)ATAIOPort::ATAIOP_DATA,word);
		}
	}
	
	
	outb((ushort)ATAIOPort::ATAIOP_COMMAND_STATUS, (byte)ATAIOCommand::ATAIOC_FLUSH);
	
	return true;
}

void ATAController::PrimaryHandler(SystemProvider& provider)
{
    provider.GetVGATextSystem()->PrintText("ATA IRQ");
    provider.GetCPUSystem()->GetPIC().SendEOI(cpu::IRQType::IRQT_ATA_PRIMARY);
}

}
