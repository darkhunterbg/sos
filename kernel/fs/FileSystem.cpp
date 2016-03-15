#include "FileSystem.h"
#include "../utils.h"
#include "../SystemProvider.h"

namespace fs
{
FileSystem::FileSystem()
{
    ataController = new ATAController();

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

    fatStartSector = bootRecord.reservedSectorsCount;
    rootStartSector = fatStartSector + extendedRecord.sectorsPerFAT * bootRecord.fatCount;
}

FileSystem::~FileSystem()
{
    delete ataController;
}

ATAController& FileSystem::GetATAController()
{
    return *ataController;
}

FSID FileSystem::GetFATNextCluster(FSID cluster)
{
    if(cluster < 0)
	return -1;

    uint fatOffset = (cluster + extendedRecord.fileSystemInfoSector + 1) * 4;
    uint fatSector = fatStartSector + (fatOffset / ATAController::SECTOR_SIZE);
    uint entryOffset = (fatOffset % ATAController::SECTOR_SIZE);

    //Load fat sector and get entry
    byte buffer[ATAController::SECTOR_SIZE];

    ataController->Read(fatSector, 1, buffer);

    //remember to ignore the high 4 bits.
    uint tableValue = *(uint*)(buffer + entryOffset) & 0x0FFFFFFF;

    if(tableValue < extendedRecord.fileSystemInfoSector + 1 || tableValue == (uint)0x0FFFFFFF)
	return -1;

    return (FSID)(tableValue - extendedRecord.fileSystemInfoSector - 1);
}

FSID FileSystem::SearchDir(FSID currentDir, const char* name, uint nameLength, const char* ext, bool isDir)
{
}

uint FileSystem::GetEntries(FSID dir, FSEntry* entries, uint maxEntries)
{
    byte buffer[ATAController::SECTOR_SIZE];
    uint sector = dir * CLUSTER_SIZE + rootStartSector;

    uint result = 0;

    for(uint i = 0; i < CLUSTER_SIZE; ++i)
	{

	    ataController->Read(sector + i, 1, buffer);

	    bool done = false;

	    for(uint j = 0; j < ATAController::SECTOR_SIZE; j += sizeof(FAT32Object))
		{
		    if(result == maxEntries - 1)
			{
			    done = true;
			    break;
			}

		    if(buffer[j] == 0)
			{
			    //No mo entries
			    done = true;
			    break;
			}
		    if(buffer[j] == 0xE5)
			{
			    //Unused
			    continue;
			}
		    if(buffer[j + 11] == (byte)FAT32ObjectAttribte::FAT32OA_LONG_FILE_ENTRY)
			{
				//SystemProvider::instance->GetVGATextSystem()->PrintText("LFN\n");
				
			    continue;
			}


		    FAT32Object& obj = *reinterpret_cast<FAT32Object*>(buffer + j);
			
			
		    if(!(byte)obj.attributes & (byte)FAT32ObjectAttribte::FAT32OA_ARCHIVE)
			{
			    //Deleted
			    continue;
			}

			 if((byte)obj.attributes & (byte)FAT32ObjectAttribte::FAT32OA_VOLUME_ID)
			{
			    //System
			    continue;
			}

		    entries[result].id = (((int)obj.firstClusterH) << 16) + obj.firstCluserL;
		    entries[result].isDirectory = (byte)obj.attributes & (byte)FAT32ObjectAttribte::FAT32OA_DIRECTORY;
		    entries[result].size = obj.size;
		    uint length = utils::StringCopy(obj.name, entries[result].name, 11);
		  //  entries[result].name[length + 1] = '.';
		  //  utils::StringCopy(obj.name, entries[result].name + length + 1, 3);
			
			++result;
		}

	    if(done)
		break;
	}

    return result;
}
}
