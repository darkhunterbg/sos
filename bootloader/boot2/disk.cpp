#include "disk.h"
#include "utils.h"
#include "io.h"

DiskService::DiskService()
{
    ReadBootRecord();
}

DiskService::~DiskService()
{
}

const FAT32BootRecord& DiskService::GetBootRecord() const
{
    return bootRecord;
}

const FAT32ExtendedBootRecord& DiskService::GetExtendedBootRecord() const
{
    return extendedRecord;
}

void DiskService::ReadBootRecord()
{
    byte* ptr = reinterpret_cast<byte*>(BOOT_RECORD_ADDRESS);

    utils::Copy(ptr + 3, bootRecord.oem, 8);
    bootRecord.oem[8] = '\0';
    utils::Copy(ptr + 11, &bootRecord.sectorSize, 2);
    utils::Copy(ptr + 13, &bootRecord.clusterSectors, 1);
    utils::Copy(ptr + 14, &bootRecord.reservedSectorsCount, 2);
    utils::Copy(ptr + 16, &bootRecord.fatCount, 1);
    utils::Copy(ptr + 17, &bootRecord.directoryEntiresCount, 2);
    utils::Copy(ptr + 19, &bootRecord.totalSectors, 2);
    utils::Copy(ptr + 21, &bootRecord.mediaDescriptorType, 1);
    utils::Copy(ptr + 24, &bootRecord.trackSectors, 2);
    utils::Copy(ptr + 26, &bootRecord.headsPerCylinder, 2);
    utils::Copy(ptr + 28, &bootRecord.hiddenSectorsCount, 4);
    utils::Copy(ptr + 32, &bootRecord.largeSectorsCount, 4);

    utils::Copy(ptr + 36, &extendedRecord.sectorsPerFAT, 4);
    utils::Copy(ptr + 40, &extendedRecord.flags, 2);
    utils::Copy(ptr + 42, &extendedRecord.version, 2);
    utils::Copy(ptr + 44, &extendedRecord.rootDirCluster, 4);
    utils::Copy(ptr + 48, &extendedRecord.fileSystemInfoSector, 2);
    utils::Copy(ptr + 50, &extendedRecord.backupBootSector, 2);
    utils::Copy(ptr + 64, &extendedRecord.driveNumber, 1);
    utils::Copy(ptr + 66, &extendedRecord.signature, 1);
    utils::Copy(ptr + 67, &extendedRecord.volumeID, 4);
    utils::Copy(ptr + 71, &extendedRecord.volumeLabel, 11);
    extendedRecord.volumeLabel[11] = '\0';
    utils::Copy(ptr + 82, extendedRecord.identifier, 8);
    extendedRecord.identifier[8] = '\0';
    // extendedRecord = reinterpret_cast<FAT32ExtendedBootRecord*>(BOOT_RECORD_ADDRESS + 36) ;
}

bool DiskService::DetectPrimaryDisk()
{
    primaryDiskInfo.detected = false;

    outb((ushort)ATAIOPort::ATAIOP_DRIVE_SELECT, (byte)ATAIOCommand::ATAIOC_DRIVE_MASTER);
    outb((ushort)ATAIOPort::ATAIOP_SECTOR_COUNT, 0x00);
    outb((ushort)ATAIOPort::ATAIOP_LBA_LOW, 0x00);
    outb((ushort)ATAIOPort::ATAIOP_LBA_MID, 0x00);
    outb((ushort)ATAIOPort::ATAIOP_LBA_HIGH, 0x00);
    outb((ushort)ATAIOPort::ATAIOP_COMMAND_STATUS, (byte)ATAIOCommand::ATAIOC_IDENTITY);

    byte status = 0;
    while(true)
	{
	    status = inb((ushort)ATAIOPort::ATAIOP_COMMAND_STATUS);

	    if(status == 0)
		{
		    //Does not exist
		    return false;
		}

	    if(status & 0x80)
		{
		    //Still busy
		    continue;
		}

	    if(inb((ushort)ATAIOPort::ATAIOP_LBA_MID) || inb((ushort)ATAIOPort::ATAIOP_LBA_HIGH))
		{
		    //Not an ATA
		    return false;
		}

	    if(status & 0x00)
		{
		    //Error
		    return false;
		}

	    if(status & 0x08)
		{
		    //Drive detected
		    primaryDiskInfo.detected = true;
		    break;
		}
	}

    ushort data[256];
    for(uint i = 0; i < 256; ++i)
	data[i] = inw((ushort)ATAIOPort::ATAIOP_DATA);

    primaryDiskInfo._type = data[0];

    primaryDiskInfo.lba28Sectors = data[61];
    primaryDiskInfo.lba28Sectors << sizeof(ushort);
    primaryDiskInfo.lba28Sectors += data[60];

    primaryDiskInfo.lba48Sectors = data[103];
    for(int i = 3; i >= 0; --i)
	{
	    primaryDiskInfo.lba48Sectors << sizeof(ushort);
	    primaryDiskInfo.lba48Sectors += data[100 + i];
	}

    primaryDiskInfo.lba48Supported = data[83] & (1 << 10);
    primaryDiskInfo.udmaSupported = data[88] & 0x00FF;
    primaryDiskInfo.currentUdma = data[88] & 0xFF00;
    primaryDiskInfo.pin80Cable = data[93] & (1 << 12);

    return true;
}
