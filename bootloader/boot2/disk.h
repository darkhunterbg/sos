#include "types.h"


struct FAT32ExtendedBootRecord
{
    uint sectorsPerFAT;
    ushort flags;
    ushort version;
    uint rootDirCluster;
    ushort fileSystemInfoSector;
    ushort backupBootSector;
    uint _reserved[3];
    byte driveNumber;
    byte _winNtFlags;
    byte signature;
    uint volumeID;
    char volumeLabel[11];
    char identifier[8];
};// 56 bytes but it should be 54

struct FAT32BootRecord
{
    byte _infiniteloop[3];
    char oem[8];
    ushort sectorSize;
    byte clusterSectors;
    ushort reservedSectorsCount;
    byte fatCount;
    ushort directoryEntiresCount;
    ushort totalSectors;
    byte mediaDescriptorType;
    ushort _sectorsPerFAT;
    ushort trackSectors;
    ushort headsPerCylinder;
    uint hiddenSectorsCount;
    uint largeSectorsCount;
	
	//FAT32ExtendedBootRecord extended;
}; // 40 bytes, but it shoud be 32

//inline constexpr bool _assert_fat_structs_size()
//{
//    static_assert(sizeof(FAT32BootRecord) == 36 , "FAT32BootRecord is not 36 bytes!");
//    static_assert(sizeof(FAT32ExtendedBootRecord) == 54, "FAT32ExtendedBootRecord is not 54 bytes!");
//    return true;
//}

class DiskService
{
    DiskService(const DiskService&) = delete;
    DiskService& operator=(const DiskService&) = delete;

  private:
    FAT32BootRecord* bootRecord = nullptr;
    FAT32ExtendedBootRecord* extendedRecord = nullptr;

	const uint BOOT_RECORD_ADDRESS = 0x0 + 0x7c00;
  public:
    DiskService();
    ~DiskService();
	
	const FAT32BootRecord& GetBootRecord() const;
	const FAT32ExtendedBootRecord& GetExtendedBootRecord() const;
};
