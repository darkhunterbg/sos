#include "disk.h"

DiskService::DiskService()
{
    bootRecord = reinterpret_cast<FAT32BootRecord*>(BOOT_RECORD_ADDRESS);
    extendedRecord = reinterpret_cast<FAT32ExtendedBootRecord*>(BOOT_RECORD_ADDRESS + 36) ;
}

DiskService::~DiskService()
{
}

const FAT32BootRecord& DiskService::GetBootRecord() const
{
    return *bootRecord;
}

const FAT32ExtendedBootRecord& DiskService::GetExtendedBootRecord() const
{
    return *extendedRecord;
}
