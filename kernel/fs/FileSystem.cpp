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

FSID FileSystem::GetNextFreeCluster(FSID start)
{
    uint fatSector = fatStartSector + (start / ATAController::SECTOR_SIZE);
    uint fatOffset = (start)*4;
    uint entryOffset = (fatOffset % ATAController::SECTOR_SIZE) / 4;

    byte buffer[ATAController::SECTOR_SIZE];

    uint result = entryOffset;

    for(uint i = 0; i < extendedRecord.sectorsPerFAT; ++i)
	{
	    ataController->Read(fatSector, 1, buffer);
	    uint* table = (uint*)(buffer);
	    for(uint j = entryOffset; j < ATAController::SECTOR_SIZE / 4; ++j)
		{
		    uint cluster = table[j];
		    if(cluster == 0)
			return result;

		    ++result;
		}

	    ++fatSector;
	    entryOffset = 0;
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
    result.parentID = 0;
    result.parentOffset = 0;
    result.lfnEntries = 0;

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

    uint lfnEntries = 0;

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
				    ++lfnEntries;
				    FAT32LongFileEntry& lfnObj = *reinterpret_cast<FAT32LongFileEntry*>(buffer + j);

				    char tmp[LFN_ENTRY_SIZE];

				    int n = 0;

				    n += utils::StringUTFCopy(lfnObj.firstChar, tmp + n, 10);
				    n += utils::StringUTFCopy(lfnObj.secondChar, tmp + n, 12);
				    n += utils::StringUTFCopy(lfnObj.thirdChar, tmp + n, 4);

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

			    entry.parentID = dir.id;
			    entry.parentOffset = (i * ATAController::SECTOR_SIZE + j) / sizeof(FAT32Object);
			    entry.id = (((int)obj.firstClusterH) << 16) + obj.firstCluserL;
			    entry.isDirectory = (byte)obj.attributes & (byte)FAT32ObjectAttribte::FAT32OA_DIRECTORY;
			    entry.size = obj.size;
			    entry.lfnEntries = lfnEntries;

			    lfnEntries = 0;
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

FSID FileSystem::StoreOnDisk(FSID parent, const FAT32Object& entry, FAT32LongFileEntry* lfnEntries, uint lfnCount)
{
    byte* buffer = new byte[ATAController::SECTOR_SIZE * CLUSTER_SIZE];

    uint neededEntries = lfnCount + 1;
    FSID cluster = parent;
    uint clusterEntryOffset = 0;

    FSID currentCluster = cluster;

    bool found = false;

    while(!found)
	{
	    uint sector = GetSectorForCluster(currentCluster);
	    //Read directory entries
	    for(uint i = 0; i < CLUSTER_SIZE; ++i)
		{
		    ataController->Read(sector + i, 1, buffer + i * ATAController::SECTOR_SIZE);
		}

	    for(uint i = 0; i < ATAController::SECTOR_SIZE * CLUSTER_SIZE; i += sizeof(FAT32Object))
		{
		    if(buffer[i] == 0 || buffer[i] == UNUSED_FAT_ENTRY)
			{
			    if(neededEntries == lfnCount + 1)
				clusterEntryOffset = i;

			    //Free entry
			    --neededEntries;
			    if(neededEntries == 0)
				{
				    found = true;
				    break;
				}
			}
		    else
			{
			    //Nope, continue
			    neededEntries = lfnCount + 1;

			    cluster = currentCluster;
			}
		}

	    if(!found)
		{
		    currentCluster = GetNextFreeCluster(currentCluster);
		}
	}

    //Cluster is start
    //clusterEntryOffset is offset in the cluster by bytes

    neededEntries = lfnCount + 1;

    uint sector = GetSectorForCluster(cluster);

    uint offsetFromEntry = clusterEntryOffset + lfnCount;

    while(neededEntries > 0)
	{
	    SystemProvider::instance->GetVGATextSystem()->PrintNumber(neededEntries);
	    SystemProvider::instance->GetVGATextSystem()->PrintChar(' ');

	    for(uint i = 0; i < CLUSTER_SIZE; ++i)
		{
		    ataController->Read(sector + i, 1, buffer + i * ATAController::SECTOR_SIZE);
		}

	    for(uint i = clusterEntryOffset; i < ATAController::SECTOR_SIZE * CLUSTER_SIZE; i += sizeof(FAT32Object))
		{
		    if(neededEntries == 1)
			{
			    FAT32Object* write = (FAT32Object*)(buffer + i);
			    *write = entry;
			}
		    else
			{
			    FAT32LongFileEntry* write = (FAT32LongFileEntry*)(buffer + i);
			    *write = lfnEntries[neededEntries - 2];
			}

		    --neededEntries;

		    if(neededEntries == 0)
			break;
		}

	    for(uint i = 0; i < CLUSTER_SIZE; ++i)
		{
		    ataController->Write(sector + i, 1, buffer + i * ATAController::SECTOR_SIZE);
		}

	    sector = GetSectorForCluster(currentCluster);
	    clusterEntryOffset = 0;
	}

    if(cluster != currentCluster)
	{
	    SetFATClusterValue(cluster, currentCluster);
	    SetFATClusterValue(currentCluster, USED_CLUSTER);
	}

    delete[] buffer;
    return offsetFromEntry;
}

CreateResult FileSystem::CreateEntry(const char* name, uint nameLength, FSEntry parent, bool isDir, FSEntry& result)
{

    uint lfnEntries = nameLength / LFN_ENTRY_SIZE;
    if(nameLength <= 11)
	lfnEntries = 0;
    else if(lfnEntries % LFN_ENTRY_SIZE != 0)
	++lfnEntries;

    //find free cluster

    if(isDir)
	{
	    FSID freeCluster = GetNextFreeCluster(parent.id);
	    if(freeCluster < 0)
		return CreateResult::INVALID_PARENT;

	    SetFATClusterValue(freeCluster, USED_CLUSTER);
	    result.id = freeCluster;
	}
    else
	result.id = 0;

    result.isDirectory = isDir;
    result.size = 0;
    result.parentID = parent.id;
    utils::StringCopy(name, result.name, 256);

    //Create all entries;

    FAT32Object obj;

    FAT32LongFileEntry lfnObj[20];

    obj.attributes = isDir ? FAT32ObjectAttribte::FAT32OA_DIRECTORY : FAT32ObjectAttribte::FAT32OA_ARCHIVE;

    if(lfnEntries == 0)
	{
	    utils::Copy(name, obj.name, 11);
	    for(uint j = nameLength; j < 11; ++j)
		obj.name[j] = ' ';
	}
    else
	{

	    utils::Copy(name, obj.name, 11);
	    utils::Copy("~1", obj.name + 6, 2);

	    for(uint j = 8; j < 11; ++j)
		obj.name[j] = ' ';

	    if(!isDir)
		{
		    const char* ext = utils::GetExtension(name, nameLength);
		    uint size = utils::StringLength(ext);
		    size = size < 3 ? 3 : size;
		    utils::Copy(ext, obj.name + 8, size);
		}

	    byte checkSum = 0;
	    for(uint i = 0; i < 11; ++i)
		{
		    checkSum = (((checkSum & 1) << 7) | ((checkSum & 0xfe) >> 1)) + obj.name[i];
		}

	    uint n = 0;

	    for(uint i = 0; i < lfnEntries; ++i)
		{
		    FAT32LongFileEntry& e = lfnObj[i];
		    e.attributes = FAT32ObjectAttribte::FAT32OA_LONG_FILE_ENTRY;
		    e.order = i + 1;
		    if(i == lfnEntries - 1)
			e.order |= 0b01000000;
		    e._zero = 0;
		    e.checksum = checkSum;
		    e.type = 0;

		    SystemProvider::instance->GetVGATextSystem()->PrintNumber(e.checksum, vga::NumberFormatting::NF_HEX);
		    SystemProvider::instance->GetVGATextSystem()->NewLine();

		    n += utils::StringCopyUTF(name + n, e.firstChar, nameLength - n, 10);
		    n += utils::StringCopyUTF(name + n, e.secondChar, nameLength - n, 12);
		    n += utils::StringCopyUTF(name + n, e.thirdChar, nameLength - n, 4);
		}
	}
    obj.size = 0;
    obj.firstCluserL = result.id & 0xFFFF;
    obj.firstClusterH = result.id & 0xFFFF0000;

    result.lfnEntries = lfnEntries;

    result.parentOffset = StoreOnDisk(parent.id, obj, lfnObj, lfnEntries);

    return CreateResult::CS_SUCCESS;
}

CreateResult FileSystem::CreateDirectory(const char* name, FSEntry parent, FSEntry& result)
{
    return CreateEntry(name, utils::StringLength(name), parent, true, result);
}

CreateResult FileSystem::CreateFile(const char* name, FSEntry parent, FSEntry& result)
{
    return CreateEntry(name, utils::StringLength(name), parent, false, result);
}

bool FileSystem::Delete(FSEntry entry)
{
    if(entry.id == GetRoot().id)
	return false;

    byte* buffer = new byte[ATAController::SECTOR_SIZE * CLUSTER_SIZE];

    if(entry.isDirectory)
	{
	    //Delete all entries in the dir
	    FSEntry entries[ 32];
		uint count = GetEntries(entry,entries,32);
		for(uint i=0;i<count;++i)
		{
			Delete(entries[i]);
		}
	}
	


    //Free from FAT
    if(entry.id != 0)
	{
	    FSID cluster = entry.id;
	    while(cluster <= USED_CLUSTER)
		{
		    FSID remove = cluster;
		  //  SetFATClusterValue(remove, FREE_CLUSTER);
		    cluster = GetFATNextCluster(cluster);
		}
	}


    //Delete the entry
    uint sector = GetSectorForCluster(entry.parentID);

    //TODO - offset in chained clusters

    //Read cluster where entry exist mark it as unused
    for(uint i = 0; i < CLUSTER_SIZE; ++i)
	{
	    ataController->Read(sector + i, 1, buffer + i * ATAController::SECTOR_SIZE);
	}

    FAT32Object* objects = (FAT32Object*)buffer;

    for(uint i = 0; i < entry.lfnEntries + 1; ++i)
	objects[entry.parentOffset - i].name[0] = UNUSED_FAT_ENTRY;

    for(uint i = 0; i < CLUSTER_SIZE; ++i)
	{
	    ataController->Write(sector + i, 1, buffer + i * ATAController::SECTOR_SIZE);
	}

    delete[] buffer;
    return true;
}
}
