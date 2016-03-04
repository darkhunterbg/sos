#include "disk.h"
#include "utils.h"

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
