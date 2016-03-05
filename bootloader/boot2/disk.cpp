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
    //
    //	vgaService.Print(diskService.GetBootRecord().reservedSectorsCount +
    //diskService.GetExtendedBootRecord().sectorsPerFAT * diskService.GetBootRecord().fatCount);
    //
}

bool DiskService::Poll()
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

bool DiskService::DetectPrimaryDisk()
{
    primaryDiskInfo.detected = false;

    outb((ushort)ATAIOPort::ATAIOP_DRIVE_SELECT, (byte)ATAIOCommand::ATAIOC_DRIVE_SELECT);
    outb((ushort)ATAIOPort::ATAIOP_SECTOR_COUNT, 0x00);
    outb((ushort)ATAIOPort::ATAIOP_LBA_LOW, 0x00);
    outb((ushort)ATAIOPort::ATAIOP_LBA_MID, 0x00);
    outb((ushort)ATAIOPort::ATAIOP_LBA_HIGH, 0x00);
    outb((ushort)ATAIOPort::ATAIOP_COMMAND_STATUS, (byte)ATAIOCommand::ATAIOC_IDENTITY);

    if(!Poll())
	return false;

    primaryDiskInfo.detected = true;

    ushort data[256];
    for(uint i = 0; i < 256; ++i)
	data[i] = inw((ushort)ATAIOPort::ATAIOP_DATA);

    //primaryDiskInfo._type = data[0];

    // primaryDiskInfo.lba28Sectors = data[61];
    // primaryDiskInfo.lba28Sectors = primaryDiskInfo.lba28Sectors << sizeof(ushort);
    // primaryDiskInfo.lba28Sectors += data[60];

    primaryDiskInfo.lba48Sectors = data[103];
    for(int i = 3; i >= 0; --i)
	{
	    primaryDiskInfo.lba48Sectors = primaryDiskInfo.lba48Sectors << sizeof(ushort);
	    primaryDiskInfo.lba48Sectors += data[100 + i];
	}

    primaryDiskInfo.lba48Supported = data[83] & (1 << 10);
    //primaryDiskInfo.udmaSupported = data[88] & 0x00FF;
    // primaryDiskInfo.currentUdma = data[88] & 0xFF00;
    // primaryDiskInfo.pin80Cable = data[93] & (1 << 12);

    return true;
}

bool DiskService::ReadFromHDD(ulong startSector, ushort lengthSectors, byte* outBuffer)
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
	    if(!Poll())
		return false;

	    for(uint i = 0; i < 256; ++i)
		{
		    ushort data = inw((ushort)ATAIOPort::ATAIOP_DATA);
		    outBuffer[0] = data & 0xFF;
		    outBuffer[1] = data >> 8 & 0xFF;
		    outBuffer += 2;
		}

	    //	    int x = 0;
	    //	    for(uint i = 0; i < 1000000; ++i)
	    //		{
	    //			++x;
	    //		}
	}

    return true;
}

void DiskService::DisableInterrups()
{
    outb((ushort)ATAIOPort::ATAIOP_CONTROL_ALT_STATUS, (byte)ATAIOCommand::ATAIOC_C_NO_INTERRUPTS);
    Poll();
}

ulong DiskService::GetRootSector() const
{
    return bootRecord.reservedSectorsCount + extendedRecord.sectorsPerFAT * bootRecord.fatCount;
}

long DiskService::GetDirectoryCluster(ulong currentDirCluster, const char* dirName, uint dirNameLength)
{
    return GetObjectCluster(currentDirCluster, dirName, dirNameLength, nullptr, true);
}
long DiskService::GetObjectCluster(ulong currentDir, const char* name, uint nameLength, const char* ext, bool isDir)
{
    //FIND IF DIR EXISTS
    //0 Load fat table for root
    ulong sector = GetRootSector();
    sector += currentDir * DiskService::CLUSTER_SIZE_SECTORS;
    //  uint* fatTable = static_cast<uint*>(memoryService.Allocate(sizeof(uint) * 1 * 128));
    // diskService.ReadFatTable(fatTable);
    //
    //1: Load first sector from root in memory

    byte buffer[DiskService::SECTOR_SIZE_BYTES];
    ReadFromHDD(sector, 1, buffer);
    //2: Search entries for Directory

    long dirCluster = -1;
    for(uint i = 0; i < DiskService::SECTOR_SIZE_BYTES; i += sizeof(FAT32Object))
	{
	    //ATTRIBUTES ARE FUCNING UNRELIABLE

	    if(buffer[i] == 0)
		//No more entries! file not found
		break;
	    if(buffer[i] == 0xE5)
		//Unused
		continue;
	    if(buffer[i + 11] == (byte)FAT32ObjectAttribte::FAT32OA_LONG_FILE_ENTRY)
		//Long file entry
		continue;

	    FAT32Object& obj = *reinterpret_cast<FAT32Object*>(buffer + i);

	    //vgaService.Print(obj->name,11);
	    //vgaService.Print((uint)obj->attributes);
	    //vgaService.Print('\n');

	    if(isDir)
		{
		    if(!(byte)obj.attributes & (byte)FAT32ObjectAttribte::FAT32OA_DIRECTORY)
			continue;
		}
	    else if(!(byte)obj.attributes & (byte)FAT32ObjectAttribte::FAT32OA_ARCHIVE)
		continue;

	    if(!isDir && !utils::Compare(obj.name + 8, ext, 3))
		continue;

	    if(utils::Compare(obj.name, name, nameLength))
		{
		    dirCluster = obj.firstClusterH;
		    dirCluster = dirCluster << sizeof(ushort);
		    dirCluster += obj.firstCluserL;
		    dirCluster -= 2;
		    break;
		}
	    //Do the same for 8 entries (aka whole cluster)
	    //If at the end of the cluster there are still entries,
	    //go to the FAT table and follow next cluster chain
	}

    return dirCluster;
}

long DiskService::GetFileCluster(ulong currentDirCluster, const char* fileName, uint fileNameLength, const char* extension)
{
    return GetObjectCluster(currentDirCluster, fileName, fileNameLength, extension, false);
}

bool DiskService::LoadFile(ulong fileCluster, void* address)
{
    uint fat[128];
    ReadFromHDD(bootRecord.reservedSectorsCount, 1, (byte*)fat);

    byte* buffer = (byte*)address;
    ulong sector = GetRootSector();
    uint cluster = fileCluster;
    do
	{
	    for(uint i = 0; i < DiskService::CLUSTER_SIZE_SECTORS; ++i)
		{
		    ReadFromHDD(sector + cluster * DiskService::CLUSTER_SIZE_SECTORS + i, 1, buffer);
		    buffer += DiskService::SECTOR_SIZE_BYTES;
		}

	    cluster = fat[cluster + 2];
	    cluster = (cluster & 0x0FFFFFFF) - 2;
		

	}
    while(cluster + 2 < 0x0FFFFFF7);

    return true;
}
