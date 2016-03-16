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
    clusterIdOffset = extendedRecord.fileSystemInfoSector + 1;
}

FileSystem::~FileSystem()
{
    delete ataController;
}

ATAController& FileSystem::GetATAController()
{
    return *ataController;
}

uint FileSystem::GetSectorForCluster(FSID cluster)
{
    return (cluster - clusterIdOffset) * CLUSTER_SIZE + rootStartSector;
}

FSID FileSystem::GetFreeCluster()
{
    byte buffer[ATAController::SECTOR_SIZE];

    uint sector = fatStartSector;

    uint result = 0;
    ;

    for(uint i = 0; i < extendedRecord.sectorsPerFAT; ++i)
	{
	    ataController->Read(sector, 1, buffer);
	    uint* table = (uint*)(buffer);
	    for(uint j = 0; j < ATAController::SECTOR_SIZE / 4; ++j)
		{
		    uint cluster = table[j];
		    if(cluster == 0)
			return result;

		    ++result;
		}

	    sector += ATAController::SECTOR_SIZE;
	}

    return -1;
}
FSID FileSystem::GetLastCluster(FSID cluster)
{
    FSID result = GetFATNextCluster(cluster);
    while(result != -1)
	result = GetFATNextCluster(result);

    return result;
}

FSID FileSystem::GetFATNextCluster(FSID cluster)
{
    if((uint)cluster < clusterIdOffset)
	return -1;

    uint fatOffset = (cluster)*4;
    uint fatSector = fatStartSector + (fatOffset / ATAController::SECTOR_SIZE);
    uint entryOffset = (fatOffset % ATAController::SECTOR_SIZE);

    //Load fat sector and get entry
    byte buffer[ATAController::SECTOR_SIZE];

    ataController->Read(fatSector, 1, buffer);

    //remember to ignore the high 4 bits.
    uint tableValue = *(uint*)(buffer + entryOffset) & USED_CLUSTER;

    if(tableValue == 0 || tableValue == USED_CLUSTER)
	return -1;

    return tableValue;
}
void FileSystem::SetFATClusterValue(FSID cluster, uint value)
{
    byte buffer[512];

    uint fatOffset = (cluster)*4;
    uint fatSector = fatStartSector + (fatOffset / ATAController::SECTOR_SIZE);
    uint entryOffset = (fatOffset % ATAController::SECTOR_SIZE) / 4;

    ataController->Read(fatSector, 1, buffer);

    uint* tableValue = (uint*)(buffer); //
    tableValue[entryOffset] = value;

    ataController->Write(fatSector, 1, buffer);
}

FSEntry FileSystem::GetRoot()
{
    FSEntry result;

    result.id = 2;
    utils::StringCopy("/", result.name, 2);
    result.isDirectory = true;
    result.size = 0;

    return result;
}

uint FileSystem::GetEntries(FSEntry dir, FSEntry* entries, uint maxEntries)
{
    if(!dir.isDirectory)
	return 0;

    byte buffer[ATAController::SECTOR_SIZE];
    uint sector = 0;

    uint result = 0;

    char lfn[256];
    lfn[0] = 0;

    uint lfnOffset = 255;

    bool done = false;

    FSID cluster = dir.id;

    while(!done)
	{
	    sector = GetSectorForCluster(cluster);

	    for(uint i = 0; i < CLUSTER_SIZE; ++i)
		{

		    ataController->Read(sector + i, 1, buffer);

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
			    if(buffer[j] == UNUSED_FAT_ENTRY)
				{
				    //Unused
				    continue;
				}
			    if(buffer[j + 11] == (byte)FAT32ObjectAttribte::FAT32OA_LONG_FILE_ENTRY)
				{
				    FAT32LongFileEntry& lfnObj = *reinterpret_cast<FAT32LongFileEntry*>(buffer + j);

				    char tmp[13];

				    int n = 0;

				    for(int k = 0; k < 10; k += 2)
					{
					    if((byte)lfnObj.firstChar[k] == 0xFF)
						break;

					    tmp[n] = lfnObj.firstChar[k];
					    ++n;
					}
				    for(int k = 0; k < 12; k += 2)
					{
					    if((byte)lfnObj.secondChar[k] == 0xFF)
						break;

					    tmp[n] = lfnObj.secondChar[k];
					    ++n;
					}
				    for(int k = 0; k < 4; k += 2)
					{
					    if((byte)lfnObj.thirdChar[k] == 0xFF)
						break;

					    tmp[n] = lfnObj.thirdChar[k];
					    ++n;
					}

				    tmp[n] = 0;

				    utils::Copy(tmp, lfn + lfnOffset - n, n);
				    lfn[255] = 0;
				    lfnOffset -= n;

				    //Only 6 bits are for order
				    // SystemProvider::instance->GetVGATextSystem()->PrintText(lfn + lfnOffset);
				    //SystemProvider::instance->GetVGATextSystem()->PrintChar(' ');
				    // SystemProvider::instance->GetVGATextSystem()->PrintText(tmp);
				    //SystemProvider::instance->GetVGATextSystem()->NewLine();

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

			    FSEntry entry;

			    entry.id = (((int)obj.firstClusterH) << 16) + obj.firstCluserL;
			    entry.isDirectory = (byte)obj.attributes & (byte)FAT32ObjectAttribte::FAT32OA_DIRECTORY;
			    entry.size = obj.size;

			    //SystemProvider::instance->GetVGATextSystem()->PrintText(lfn);
			    //SystemProvider::instance->GetVGATextSystem()->NewLine();

			    if(lfnOffset == 255)
				{

				    int index = utils::FindChar(obj.name, ' ', 11);

				    utils::StringAppend(obj.name, entry.name, index, 256);
				    if(!entry.isDirectory)
					{
					    utils::StringAppend(".", entry.name, 1, 256);
					    index = utils::FindChar(obj.name + 8, ' ', 3);
					    if(index < 0)
						index = 0;
					    utils::StringAppend(obj.name + index + 8, entry.name, 3, 256);
					}
				}
			    else
				{
				    utils::StringAppend(lfn + lfnOffset, entry.name, 256, 256);
				    lfn[0] = 0;
				    lfnOffset = 255;
				}

			    if(entry.isDirectory && (utils::StringEqual(entry.name, ".", 2) || utils::StringEqual(entry.name, "..", 3)))
				continue;

			    entries[result] = entry;

			    ++result;
			}

		    if(done)
			break;
		}

	    if(!done)
		{
		    cluster = GetFATNextCluster(cluster);
		}
	}

    return result;
}

FSEntry FileSystem::CreateDirectory(const char* name, uint nameLength, FSEntry parent)
{
    //find free cluster
    FSID freeCluster = GetFreeCluster();
    if(freeCluster < 0)
	return FSEntry();

    FSEntry result;
    result.id = freeCluster;
    result.isDirectory = true;
    result.size = 0;
    utils::StringCopy(name, result.name, 256);

    byte* buffer = new byte[ATAController::SECTOR_SIZE * CLUSTER_SIZE];

    //Read directory entries
    for(uint i = 0; i < CLUSTER_SIZE; ++i)
	{
	    uint sector = GetSectorForCluster(parent.id) + i;
	    ataController->Read(sector, 1, buffer + i * ATAController::SECTOR_SIZE);
	}

    for(uint i = 0; i < ATAController::SECTOR_SIZE * CLUSTER_SIZE; i += sizeof(FAT32Object))
	{
	    if(buffer[i] == 0 || buffer[i] == UNUSED_FAT_ENTRY)
		{
		    //Free entry

		    FAT32Object& obj = *(FAT32Object*)(buffer + i);
		    obj.attributes = FAT32ObjectAttribte::FAT32OA_DIRECTORY;
		    for(uint j = 0; j < 11; ++j)
			obj.name[j] = ' ';
		    utils::Copy(name, obj.name, nameLength);
		    obj.size = 0;
		    obj.firstCluserL = freeCluster & 0xFFFF;
		    obj.firstClusterH = freeCluster & 0xFFFF0000;

		    break;
		}
	}

    //return result;
    //Write back the entire cluster
    for(uint i = 0; i < CLUSTER_SIZE; ++i)
	{
	    uint sector = parent.id + rootStartSector - clusterIdOffset + i;
	    ataController->Write(sector, 1, buffer + i * ATAController::SECTOR_SIZE);
	}

    //Write to the FAT table
    SetFATClusterValue(freeCluster, USED_CLUSTER);

    //TODO if cluster is full, create new cluster for this dir
    //TODO write to backup fat table
    delete[] buffer;

    return result;
}
}
