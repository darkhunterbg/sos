#pragma once
#include "../Types.h"
#include "ATAController.h"

namespace fs
{
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

enum class FAT32ObjectAttribte : byte
{
	FAT32OA_READ_ONLY = 0x01,
	FAT32OA_HIDDEN = 0x02,
	FAT32OA_SYSTEM = 0x04,
	FAT32OA_VOLUME_ID = 0x08,
	FAT32OA_DIRECTORY = 0x10,
	FAT32OA_ARCHIVE = 0x20,
	FAT32OA_LONG_FILE_ENTRY = 0x01 | 0x02 | 0x04 | 0x08
};


struct FAT32Object
{
	char name[11];
	FAT32ObjectAttribte attributes;
	byte _winNTReserved;
	byte creationTimeHMS;
	ushort creationTime;
	ushort creationDate;
	ushort accessDate;
	ushort firstClusterH;
	ushort modificationTime;
	ushort modificationDate;
	ushort firstCluserL;
	uint size;
} __attribute__ ((packed));
struct FAT32LongFileEntry
{
	byte order;
	char firstChar[10];
	FAT32ObjectAttribte attributes;
	byte type;
	byte checksum;
	char secondChar[12];
	ushort _zero;
	char thirdChar[4];
} __attribute__ ((packed));


//In sectors
typedef int FSID;

struct FSEntry
{
	 char*  name;
	FSID id;
	uint size;
	bool isDirectory;
	
	FSEntry()
	{
		name = new char[256];
		name[0] = 0;
	}
	~FSEntry()
	{
		delete[] name;
	}
};

class FileSystem
{
    FileSystem(const& FileSystem) = delete;
    FileSystem& operator=(const& FileSystem) = delete;
	
	 static const uint BOOT_RECORD_ADDRESS = 0x0 + 0x7c00;
	 static const uint FAT_ENTRY_SIZE = 4;
	 static const uint CLUSTER_SIZE = 8;
	
	private:
	ATAController* ataController = nullptr;
	uint fatStartSector;
	uint rootStartSector;
	
	
	FAT32BootRecord bootRecord;
    FAT32ExtendedBootRecord extendedRecord;

	FSID GetFATNextCluster(FSID cluster);
	FSID SearchDir(FSID currentDir, const char* name, uint nameLength, const char* ext, bool isDir);
	
	public :
	FileSystem();
	~FileSystem();
	
	uint GetEntries(FSID dir, FSEntry* buffer, uint bufferSize);

	
	
	ATAController& GetATAController();
};
}
