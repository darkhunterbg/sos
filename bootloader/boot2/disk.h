#include "types.h"

struct FAT32ExtendedBootRecord
{
    uint sectorsPerFAT;
    ushort flags;
    ushort version;
    uint rootDirCluster;
    ushort fileSystemInfoSector;
    ushort backupBootSector;
    //uint _reserved[3];
    byte driveNumber;
    //byte _winNtFlags;
    byte signature;
    uint volumeID;
    char volumeLabel[11 + 1];
    char identifier[8 + 1];
}; // 56 bytes but it should be 54

struct FAT32BootRecord
{
    //byte _infiniteloop[3];
    char oem[8 + 1];
    ushort sectorSize;
    byte clusterSectors;
    ushort reservedSectorsCount;
    byte fatCount;
    ushort directoryEntiresCount;
    ushort totalSectors;
    byte mediaDescriptorType;
    //ushort _sectorsPerFAT;
    ushort trackSectors;
    ushort headsPerCylinder;
    uint hiddenSectorsCount;
    uint largeSectorsCount;

    //FAT32ExtendedBootRecord extended;
}; // 40 bytes, but it shoud be 32

enum class ATAIOPort : ushort
{
    ATAIOP_DATA = 0x01F0,
    ATAIOP_SECTOR_COUNT = 0x01F2,
    ATAIOP_LBA_LOW = 0x01F3,
    ATAIOP_LBA_MID = 0x01F4,
    ATAIOP_LBA_HIGH = 0x01F5,
    ATAIOP_DRIVE_SELECT = 0x01F6,
    ATAIOP_COMMAND_STATUS = 0x01F7,
};
enum class ATAIOCommand : byte
{
    ATAIOC_DRIVE_MASTER = 0xA0,
    ATAIOC_DRIVE_SLAVE = 0xB0,
    ATAIOC_IDENTITY = 0xEC,
};

struct AtaIdentity
{
    bool detected;
    ushort _type;        //0: useful if the device is not a hard disk
    bool lba48Supported; //83: bit 10 is set if the drive supports LBA48 mode
    byte udmaSupported;
    byte currentUdma;   //88: the bits in the low byte tell you the supported UDMA modes, the upper byte tells you which UDMA mode is active. If the active mode is not the highest supported mode, you may want to figure out why.
    bool pin80Cable;  //93:  from a master drive on the bus: Bit 12 is supposed to be set if the drive detects an 80 pin cable.
    uint lba28Sectors;  //60 & 61: contain the total number of 28 bit LBA addressable sectors on the drive. (If non-zero, the drive supports LBA28.)
    ulong lba48Sectors; //100-103: taken as a uint64_t contain the total number of 48 bit addressable sectors on the drive. (Probably also proof that LBA48 is supported.)
};

class DiskService
{
    DiskService(const DiskService&) = delete;
    DiskService& operator=(const DiskService&) = delete;

  private:
    FAT32BootRecord bootRecord;
    FAT32ExtendedBootRecord extendedRecord;
    AtaIdentity primaryDiskInfo;

    const uint BOOT_RECORD_ADDRESS = 0x0 + 0x7c00;

    void ReadBootRecord();

  public:
    DiskService();
    ~DiskService();

    const FAT32BootRecord& GetBootRecord() const;
    const FAT32ExtendedBootRecord& GetExtendedBootRecord() const;

    bool DetectPrimaryDisk();
};
